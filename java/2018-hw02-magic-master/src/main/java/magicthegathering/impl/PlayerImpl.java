package magicthegathering.impl;

import java.util.ArrayList;
import java.util.List;
import magicthegathering.game.Card;
import magicthegathering.game.CreatureCard;
import magicthegathering.game.LandCard;
import magicthegathering.game.ManaType;
import magicthegathering.game.Player;

/**
 *
 * @author Patrik Valo
 */
public class PlayerImpl implements Player{
    
    private String name;
    private int life = INIT_LIVES;
    private List<Card> cards;
    
    /**
     * Constructor of PlayerImpl
     * @param name - name 
     */
    public PlayerImpl(String name) {
        if (name == null || name.isEmpty()) {
            throw new IllegalArgumentException("Ivalid name");
        }
        this.name = name;
    }
    
    @Override
    public String toString() {
        return name + "(" + life + ")";
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public int getLife() {
        return life;
    }

    @Override
    public void subtractLives(int lives) {
        life -= lives;
    }

    @Override
    public boolean isDead() {
        return life <= 0;
    }

    @Override
    public void initCards(List<Card> cards) {
        this.cards = cards;
    }

    @Override
    public List<Card> getCardsInHand() {
        List<Card> returnList = new ArrayList<>();
        for (Card card: cards) {
            if (!card.isOnTable()) {
                returnList.add(card);
            }
        }
        return returnList;
    }

    @Override
    public List<Card> getCardsOnTable() {
        List<Card> returnList = new ArrayList<>();
        for (Card card: cards) {
            if (card.isOnTable()) {
                returnList.add(card);
            }
        }
        return returnList;
    }
    
    private List<LandCard> findLands(List<Card> cards) {
        List<LandCard> returnList = new ArrayList<>();
        for (Card card : cards) {
            if (card instanceof LandCard) {
                returnList.add((LandCard) card);
            }            
        }
        return returnList;
    }
    
    private List<CreatureCard> findCreatures(List<Card> cards) {
        List<CreatureCard> returnList = new ArrayList<>();
        for (Card card : cards) {
            if (card instanceof CreatureCard) {
                returnList.add((CreatureCard)card);
            }            
        }
        return returnList;
    }
    
    @Override
    public List<LandCard> getLandsOnTable() {
        return findLands(getCardsOnTable());
    }

    @Override
    public List<CreatureCard> getCreaturesOnTable() {
        return findCreatures(getCardsOnTable());
    }

    @Override
    public List<LandCard> getLandsInHand() {
        return findLands(getCardsInHand());
    }

    @Override
    public List<CreatureCard> getCreaturesInHand() {
        return findCreatures(getCardsInHand());
    }

    @Override
    public void untapAllCards() {
        for (Card c : getCardsOnTable()) {
            c.untap();
        }
    }

    @Override
    public void prepareAllCreatures() {
        for (CreatureCard creature : getCreaturesOnTable()) {
            creature.unsetSummoningSickness();
        }        
    }

    @Override
    public boolean putLandOnTable(LandCard landCard) {
        if (landCard.isOnTable() || !getCardsInHand().contains(landCard)) {
            return false;
        }
        landCard.putOnTable();
        return true;
    }

    @Override
    public boolean putCreatureOnTable(CreatureCard creatureCard) {
        if (creatureCard.isOnTable() || !getCardsInHand().contains(creatureCard)) {
            return false;
        }
        
        if (!hasManaForCreature(creatureCard)) {
            return false;
        }
        
        tapManaForCreature(creatureCard);
        
        creatureCard.putOnTable();
        
        return true;
    }

    @Override
    public boolean hasManaForCreature(CreatureCard creature) {
        int[] typeManas = calculateUntappedLands();
        
        for (ManaType type : ManaType.values()) {
            if (typeManas[type.ordinal()] < creature.getSpecialCost(type)) {
                return false;
            }
        }
        return true;
    }

    @Override
    public int[] calculateUntappedLands() {
        int[] returnArray = {0, 0, 0, 0, 0};
        
        for (LandCard land : getLandsOnTable()) {
            if (!land.isTapped()) {
                returnArray[land.getManaType().ordinal()]++;
            }
        }
        return returnArray;
    }
    
    private void tapLandsWithMana(ManaType type, int count) {
        if (count <= 0) {
            return;
        }
        
        for (LandCard land : getLandsOnTable()) {
            if (count == 0) {
                return;
            }
            if (!land.isTapped() && land.getManaType() == type) {
                land.tap();
                count--;
            }
        }
    }
    @Override
    public void tapManaForCreature(CreatureCard creature) {
        for (ManaType type: ManaType.values()) {
            tapLandsWithMana(type, creature.getSpecialCost(type));
        }
    }

    @Override
    public void destroyCreature(CreatureCard creature) {
        /*if (creature.isOnTable()) {
            cards.remove(creature);
        }*/
        cards.remove(creature);
        
    }
}
