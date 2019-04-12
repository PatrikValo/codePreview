package magicthegathering.impl;

import magicthegathering.game.Card;
import magicthegathering.game.CreatureCard;
import magicthegathering.game.LandCard;
import magicthegathering.game.LandCardType;
import magicthegathering.game.ManaType;
import magicthegathering.game.Player;
import org.junit.Before;
import org.junit.Test;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

/**
 * @author Zuzana Wolfova, Patrik Majerčík
 */
public class PlayerImplTest {

    private PlayerImpl marek;
    private CreatureCardImpl kitkin;
    private LandCardImpl plains;
    private LandCardImpl swamp;
    private List<LandCard> landsAllColors;

    @Before
    public void setUp() throws Exception {
        marek = new PlayerImpl("Marek");
        plains = new LandCardImpl(LandCardType.PLAINS);
        swamp = new LandCardImpl(LandCardType.SWAMP);
        kitkin = new CreatureCardImpl(
                "Kitkin",
                Arrays.asList(ManaType.WHITE),
                2,
                1);
        marek.initCards(new ArrayList<>(Arrays.asList(
                swamp,
                plains,
                kitkin
        )));
        landsAllColors = Arrays.asList(
                new LandCardImpl(LandCardType.PLAINS),
                new LandCardImpl(LandCardType.MOUNTAIN),
                new LandCardImpl(LandCardType.FOREST),
                new LandCardImpl(LandCardType.ISLAND),
                new LandCardImpl(LandCardType.SWAMP))
        ;
    }

    @Test
    public void testNameAndLife() {
        assertEquals("Marek", marek.getName());

        assertEquals(Player.INIT_LIVES, marek.getLife());
        int subtract = 8;
        marek.subtractLives(subtract);
        assertEquals(Player.INIT_LIVES - subtract, marek.getLife());
    }


    @Test
    public void testCardsInHand() {

        for (Card card : marek.getCardsInHand()) {
            assertFalse(card.isTapped());
            assertFalse(card.isOnTable());
        }

        assertEquals(1, marek.getCreaturesInHand().size());
        assertEquals(2, marek.getLandsInHand().size());
        assertEquals(3, marek.getCardsInHand().size());
    }


    @Test
    public void testCardsOnTable() {

        putEverythingUntappedOnTable();

        for (Card card : marek.getCardsOnTable()) {
            assertFalse(card.isTapped());
            assertTrue(card.isOnTable());
        }

        assertEquals(1, marek.getCreaturesOnTable().size());
        assertEquals(2, marek.getLandsOnTable().size());
        assertEquals(3, marek.getCardsOnTable().size());
    }

    private void putEverythingUntappedOnTable() {
        marek.putLandOnTable(plains);
        marek.putLandOnTable(swamp);
        marek.putCreatureOnTable(kitkin);
        plains.untap();
    }

    @Test
    public void putLandOnTableTwice() {
        assertTrue(marek.putLandOnTable(plains));
        assertFalse(marek.putLandOnTable(plains));
    }


    @Test
    public void putCreatureOnTableCorrectly() {
        assertTrue(marek.putLandOnTable(plains));
        assertTrue(marek.putCreatureOnTable(kitkin));
    }

    @Test
    public void putCreatureOnTableWhichIsNotInHand() {
        assertTrue(marek.putLandOnTable(plains));
        assertFalse(marek.putCreatureOnTable(
                new CreatureCardImpl("White Knight", Arrays.asList(ManaType.WHITE), 1, 1)));
    }

    @Test
    public void preparedCreatureCanAttack() {
        putEverythingUntappedOnTable();
        marek.prepareAllCreatures();
        assertFalse(kitkin.hasSummoningSickness());
    }

    @Test
    public void testSummoningSickness() {
        putEverythingUntappedOnTable();
        assertTrue(marek.getCreaturesOnTable().get(0).hasSummoningSickness());
    }

    @Test
    public void testManaForCreature() {
        assertFalse(marek.hasManaForCreature(kitkin));
        marek.putLandOnTable(swamp);
        assertFalse(marek.hasManaForCreature(kitkin));
        marek.putLandOnTable(plains);
        assertTrue(marek.hasManaForCreature(kitkin));
    }

    @Test
    public void testAllManaTypes() {
        CreatureCard hybrid = new CreatureCardImpl("Hybrid",
                Arrays.asList(
                        ManaType.WHITE,
                        ManaType.RED,
                        ManaType.GREEN,
                        ManaType.BLUE,
                        ManaType.BLACK
                ), 1, 1);
        Player eva = new PlayerImpl("Eva");
        eva.initCards(Arrays.asList(
                landsAllColors.get(0), landsAllColors.get(1), landsAllColors.get(2),
                landsAllColors.get(3), landsAllColors.get(4), hybrid
        ));

        assertFalse(eva.hasManaForCreature(hybrid));
        eva.putLandOnTable(landsAllColors.get(0));
        assertFalse(eva.hasManaForCreature(hybrid));
        eva.putLandOnTable(landsAllColors.get(1));
        assertFalse(eva.hasManaForCreature(hybrid));
        eva.putLandOnTable(landsAllColors.get(2));
        assertFalse(eva.hasManaForCreature(hybrid));
        eva.putLandOnTable(landsAllColors.get(3));
        assertFalse(eva.hasManaForCreature(hybrid));
        eva.putLandOnTable(landsAllColors.get(4));
        assertTrue(eva.hasManaForCreature(hybrid));
    }

    @Test
    public void testUntappedLandsCalculation() {
        int[] lands = {0, 0, 0, 0, 0,};
        Player chris = new PlayerImpl("Chris");
        chris.initCards(new ArrayList<Card>(landsAllColors));

        assertArrayEquals(lands, chris.calculateUntappedLands());

        for (int i = 0; i < 5; i++) {
            lands[i] += 1;
            chris.putLandOnTable(landsAllColors.get(i));
            assertArrayEquals(lands, chris.calculateUntappedLands());
        }

        chris.getLandsOnTable().get(1).tap();
        lands[1] -= 1;
        assertArrayEquals(lands, chris.calculateUntappedLands());

    }

    @Test
    public void testTappedManaForCreature() {
        marek.putLandOnTable(plains);
        marek.putLandOnTable(swamp);
        marek.tapManaForCreature(kitkin);
        assertTrue(plains.isTapped());
        assertFalse(swamp.isTapped());
    }


    @Test
    public void testStringMessage() {
        assertEquals("Marek(20)", marek.toString());
    }

    @Test(expected = IllegalArgumentException.class)
    public void constructorNullTest() {
        new PlayerImpl(null);
    }

    @Test(expected = IllegalArgumentException.class)
    public void constructorEmptyTest() {
        new PlayerImpl("");
    }
}
