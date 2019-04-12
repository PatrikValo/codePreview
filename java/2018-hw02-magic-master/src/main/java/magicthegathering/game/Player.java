package magicthegathering.game;

import java.util.List;

/**
 * Player's interface.
 *
 * @author Zuzana Wolfova, Marek Sabo, Patrik Majerčík
 */
public interface Player {

    int INIT_LIVES = 20;

    /**
     * Get player's name.
     *
     * @return players name
     */
    String getName();

    /**
     * Get player's number of lives.
     *
     * @return life
     */
    int getLife();

    /**
     * Subtract player's lives.
     *
     * @param lives lives
     */
    void subtractLives(int lives);

    /**
     * Returns true, if player's lives are below or equal to 0.
     *
     * @return if a player is dead
     */
    boolean isDead();

    /**
     * Initial cards put into player's hand. Cards from the table are removed.
     * Input parameter is copied.
     *
     * @param cards to be put into player's hand
     */
    void initCards(List<Card> cards);

    /**
     * Get player's cards in hand.
     *
     * @return player's cards in hand
     */
    List<Card> getCardsInHand();

    /**
     * Get player's cards on the table.
     *
     * @return player's cards on the table
     */
    List<Card> getCardsOnTable();

    /**
     * Get player's lands on the table.
     *
     * @return player's lands on the table
     */
    List<LandCard> getLandsOnTable();

    /**
     * Get player's creatures on the table.
     *
     * @return player's creatures on the table
     */
    List<CreatureCard> getCreaturesOnTable();

    /**
     * Get player's lands in hand.
     *
     * @return player's lands in hand
     */
    List<LandCard> getLandsInHand();

    /**
     * Get player's creatures in hand.
     *
     * @return player's creatures in hand
     */
    List<CreatureCard> getCreaturesInHand();

    /**
     * Untap all cards on the table.
     */
    void untapAllCards();

    /**
     * Unset summoning sickness of all creatures.
     */
    void prepareAllCreatures();

    /**
     * Put a land from hand on table.
     *
     * @param landCard land to be put on the table
     * @return true if succeeded, false if land is not in player's hand or already on the table
     */
    boolean putLandOnTable(LandCard landCard);

    /**
     * Put a creature from hand to table. Taps lands for mana needed to summon a creature.
     *
     * @param creatureCard creature card to be put on the table
     * @return true if succeeded, false if creature is not in player's hand,
     * already on the table, or player does not have enough mana
     */
    boolean putCreatureOnTable(CreatureCard creatureCard);

    /**
     * Checks whether user has enough mana to summon the input creature.
     *
     * @param creature creature to be checked
     * @return true if has enough mana, false otherwise
     */
    boolean hasManaForCreature(CreatureCard creature);

    /**
     * Calculates how many untapped lands has player on the table.
     *
     * @return array of integers, where every number represents how many untapped lands the player has in the following
     * (ordinal) order: WHITE, RED, GREEN, BLUE, BLACK. You can use {@link ManaType#ordinal()} method.
     */
    int[] calculateUntappedLands();

    /**
     * Taps the lands needed for summoning a creature.
     *
     * @param creature creature which price needs to be paid
     */
    void tapManaForCreature(CreatureCard creature);

    /**
     * Removes creature from the game.
     *
     * @param creature creature to be removed.
     */
    void destroyCreature(CreatureCard creature);
}
