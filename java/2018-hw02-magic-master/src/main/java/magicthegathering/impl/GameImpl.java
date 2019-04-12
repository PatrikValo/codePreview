package magicthegathering.impl;

import java.util.HashSet;
import java.util.List;
import java.util.Set;
import magicthegathering.game.CreatureCard;
import magicthegathering.game.Game;
import magicthegathering.game.Generator;
import magicthegathering.game.Player;

/**
 *
 * @author Patrik Valo
 */
public class GameImpl implements Game{
    private Player[] players = new Player[2];
    private int actualIndex = 0;
    
    /**
     * Constructor of GameImpl
     * @param player1 - player1
     * @param player2 - player2
     */
    public GameImpl(Player player1, Player player2) {
        if (player1 == null || player2 == null) {
            throw new IllegalArgumentException("Null player");
        }
        
        players[0] = player1;
        players[1] = player2;
        
    }

    @Override
    public void initGame() {
        players[0].initCards(Generator.generateCards());
        players[1].initCards(Generator.generateCards());
    }

    @Override
    public void changePlayer() {
        actualIndex = (actualIndex + 1) % 2;
    }

    @Override
    public void prepareCurrentPlayerForTurn() {
        players[actualIndex].untapAllCards();
        players[actualIndex].prepareAllCreatures();
    }

    @Override
    public Player getCurrentPlayer() {
        return players[actualIndex];
    }

    @Override
    public Player getSecondPlayer() {
        return players[(actualIndex + 1) % 2];
    }

    @Override
    public void performAttack(List<CreatureCard> creatures) {
        for (CreatureCard creature: creatures) {
            creature.tap();
        }
    }

    /**
     * Control duplicicates in List
     * @param creatures List of creatures
     * @param nullDuplicate Boolean - true - there can be null values
     *                              - false - there are no null values
     * @return false - if list contains duplicates
     *         true - otherwise
     */
    private boolean controlDuplicate(List<CreatureCard> creatures, boolean nullDuplicate) {
        Set<CreatureCard> set= new HashSet<>(creatures);

        if (set.size() != creatures.size()) {
            
            if (nullDuplicate) {
                // null duplicate control
                int count = creatures.size() - set.size() + 1;
                for (CreatureCard creature: creatures) {
                    if (creature == null) {
                        count--;
                    }
                }

                if (count != 0) {
                    return false;
                }
            } else {
                return false;
            }
        }

        return true;
    }
    @Override
    public boolean isCreaturesAttackValid(List<CreatureCard> attackingCreatures) {
        if (!controlDuplicate(attackingCreatures, false)) {
            return false;
        }
        
        List<CreatureCard>playerTable = players[actualIndex].getCreaturesOnTable();
        
        for (CreatureCard c : attackingCreatures) {
            if(c.hasSummoningSickness() || c.isTapped() || 
               !playerTable.contains(c)) {
                return false;
            }
        }
        return true;
    }

    @Override
    public boolean isCreaturesBlockValid(List<CreatureCard> attackingCreatures, List<CreatureCard> blockingCreatures) {
        if (attackingCreatures.size() != blockingCreatures.size()) {
            return false;
        }
        
        if (!getCurrentPlayer().getCardsOnTable().containsAll(attackingCreatures)) {
            return false;
        }

        for (CreatureCard creature : blockingCreatures) {
            if(creature != null && (!getSecondPlayer().getCardsOnTable().contains(creature) 
               || creature.isTapped())) {
                return false;
            }
        }
        
        if (!controlDuplicate(attackingCreatures, false) || !controlDuplicate(blockingCreatures, true)) {
            return false;
        }
        
        return true;
    }

    private boolean affectCreature(CreatureCard attacking, CreatureCard blocking) {
        return attacking.getPower() >= blocking.getToughness();
    }
    
    @Override
    public void performBlockAndDamage(List<CreatureCard> attackingCreatures, List<CreatureCard> blockingCreatures) {
        if (isCreaturesAttackValid(attackingCreatures) &&
            isCreaturesBlockValid(attackingCreatures, blockingCreatures)) {

            performAttack(attackingCreatures);

            for (int i = 0; i < attackingCreatures.size(); ++i) {
                if (blockingCreatures.get(i) == null) {
                    getSecondPlayer().subtractLives(attackingCreatures.get(i).getPower());
                } else {
                    boolean destroyAttackCreature = false;
                    boolean destroyBlockCreature = false;

                    if (affectCreature(attackingCreatures.get(i), blockingCreatures.get(i))) {
                        destroyBlockCreature = true;
                    }

                    if (affectCreature(blockingCreatures.get(i), attackingCreatures.get(i))) {
                        destroyAttackCreature = true;
                    }

                    if (destroyAttackCreature) { 
                        getCurrentPlayer().destroyCreature(attackingCreatures.get(i));
                    }
                    if (destroyBlockCreature) { 
                        getSecondPlayer().destroyCreature(blockingCreatures.get(i));
                    }

                }
            }
        }
    }
    
}
