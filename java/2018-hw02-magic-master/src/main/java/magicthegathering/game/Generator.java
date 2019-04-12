package magicthegathering.game;

import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

import static magicthegathering.game.Game.CREATURE_COUNT;
import static magicthegathering.game.Game.LAND_COUNT;
import static magicthegathering.game.Game.TOTAL_CARD_AMOUNT;
import magicthegathering.impl.CreatureCardImpl;
import magicthegathering.impl.LandCardImpl;

/**
 * Class used for generating cards.
 *
 * @author Marek Sabo, Zuzana Wolfova, Patrik Majerčík
 */
public class Generator {

    private static final int CREATURE_MAX_POWER_STRENGTH = 8;
    private static final int CREATURE_MAX_POWER_TOUGHNESS = 5;
    private static final int CREATURE_MAX_MANA = 3;

    private static final Random RANDOM = new SecureRandom();
    private static LandCard[] lands = new LandCard[LAND_COUNT];

    /**
     * Method used for generating {@link Game#TOTAL_CARD_AMOUNT} cards.
     * It generates {@link Game#LAND_COUNT} amount of lands and  {@link Game#CREATURE_COUNT} amount of creatures.
     *
     * @return generated lands and creatures
     */
    public static ArrayList<Card> generateCards() {
        Card[] cards = new Card[TOTAL_CARD_AMOUNT];

        for (int i = 0; i < LAND_COUNT; i++) {
            lands[i] = generateLand();
            cards[i] = lands[i];
        }

        for (int i = 0; i < CREATURE_COUNT; i++) {
            cards[i + LAND_COUNT] = generateCreature("Creature " + i);
        }

        return new ArrayList<Card>(Arrays.asList(cards));
    }


    private static LandCard generateLand() {
        return new LandCardImpl(LandCardType.values()[
                RANDOM.nextInt(LandCardType.values().length)
                ]);
    }

    private static CreatureCard generateCreature(String name) {
        return new CreatureCardImpl(name,
                generateCreatureManaCost(),
                RANDOM.nextInt(CREATURE_MAX_POWER_STRENGTH) + 1,
                RANDOM.nextInt(CREATURE_MAX_POWER_TOUGHNESS) + 1);
    }

    private static List<ManaType> generateCreatureManaCost() {
        List<ManaType> creatureManaCost = new ArrayList<>();
        for (int y = 0; y < RANDOM.nextInt(CREATURE_MAX_MANA) + 1; y++) {
            creatureManaCost.add( lands[RANDOM.nextInt(lands.length)].getManaType());
        }
        return creatureManaCost;
    }


}
