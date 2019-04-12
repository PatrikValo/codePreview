package magicthegathering.game;

import java.util.List;

/**
 * Game interface.
 *
 * @author Zuzana Wolfova, Marek Sabo, Patrik Majerčík
 */
public interface Game {

    /**
     * Amount of generated creatures.
     */
    int CREATURE_COUNT = 6;

    /**
     * Amount of generated lands.
     */
    int LAND_COUNT = 8;

    /**
     * Amount of generated cards.
     */
    int TOTAL_CARD_AMOUNT = CREATURE_COUNT + LAND_COUNT;

    /**
     * Generates player's cards.
     */
    void initGame();

    /**
     * Set (pick) next player.
     */
    void changePlayer();

    /**
     * Prepare player for turn: untap all the cards and unset summoning sickness on creatures.
     */
    void prepareCurrentPlayerForTurn();

    /**
     * Get current player.
     *
     * @return current player
     */
    Player getCurrentPlayer();

    /**
     * Get the other player.
     *
     * @return other player
     */
    Player getSecondPlayer();

    /**
     * Perform attack from current player to the second player.
     * All attacking creatures are tapped.
     *
     * @param creatures creatures which are going to attack
     */
    void performAttack( List<CreatureCard> creatures);

    /**
     * Checks whether creatures which are going to attack do not break any rules.
     *
     * @param attackingCreatures list of attacking creatures
     * @return true if all creatures are able to attack, false if any creature has summoning sickness,
     * is tapped, does not belong to the current player or the list contains duplicate creatures
     */
    boolean isCreaturesAttackValid( List<CreatureCard> attackingCreatures);

    /**
     * Checks whether blocking does not break any rules.
     * Null elements represent that creature is not going to be blocked.
     *
     * @param attackingCreatures list of attacking creatures
     * @param blockingCreatures  list of blocking creatures
     * @return false if lists have different length, contains duplicates elements excluding null,
     * or attacking/blocking creatures do not belong to the current/second player
     * or blocking creature is tapped
     */
    boolean isCreaturesBlockValid(List<CreatureCard> attackingCreatures, List<CreatureCard> blockingCreatures);

    /**
     * Evaluates the block, damage to the creatures, their removal, damage to the player.
     *
     * @param attackingCreatures list of attacking creatures
     * @param blockingCreatures  list of blocking creatures
     */
    void performBlockAndDamage( List<CreatureCard> attackingCreatures,  List<CreatureCard> blockingCreatures);

}
