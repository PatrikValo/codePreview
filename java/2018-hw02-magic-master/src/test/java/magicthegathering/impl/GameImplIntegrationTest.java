package magicthegathering.impl;

import magicthegathering.game.Card;
import magicthegathering.game.CreatureCard;
import magicthegathering.game.Game;
import magicthegathering.game.LandCard;
import magicthegathering.game.ManaType;
import magicthegathering.game.Player;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;

import java.text.CollationElementIterator;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

/**
 * @author Zuzana Wolfova, Patrik Majerčík
 */
public class GameImplIntegrationTest {

    private Player first;
    private Player second;
    private Game game;
    private CreatureCard creature1;
    private CreatureCard creature2;
    private CreatureCard creature3;
    private CreatureCard creature4;

    @Before
    public void setUp() {
        first = new PlayerImpl("Marek");
        second = new PlayerImpl("Zuzka");
        game = new GameImpl(first, second);

        creature1 = new CreatureCardImpl("Artifact creature",
                Collections.emptyList(),
                0,
                2);
        creature2 = new CreatureCardImpl("Hybrid creature",
                Collections.emptyList(),
                1,
                1);
        creature3 = new CreatureCardImpl("Strong creature",
                Collections.emptyList(),
                1,
                2);
        creature4 = new CreatureCardImpl("Weak creature",
                Collections.emptyList(),
                0,
                1);
        first.initCards(new ArrayList<>(Arrays.asList(creature1, creature2)));
        second.initCards(new ArrayList<>(Arrays.asList(creature3, creature4)));
    }

    @Test
    public void creatureAttackNotBelongingToCurrentPlayer() {
        CreatureCard c = new CreatureCardImpl("Rogue",
                Arrays.asList(ManaType.BLACK),
                2,
                1);
        c.putOnTable();
        c.unsetSummoningSickness();
        assertFalse(game.isCreaturesAttackValid(Arrays.asList(c)));
    }

    @Test
    public void correctAttack() {
        prepareCreatureForAttack(creature1);
        assertTrue(game.isCreaturesAttackValid(Arrays.asList(creature1)));
    }

    private void prepareCreatureForAttack(CreatureCard creature) {
        game.getCurrentPlayer().putCreatureOnTable(creature);
        creature.unsetSummoningSickness();
    }

    @Test
    public void blockHasDifferentListLength() {
        prepareCreatureForAttack(creature1);
        assertFalse(game.isCreaturesBlockValid(Arrays.asList(creature1), Arrays.asList(null, null)));
        assertFalse(game.isCreaturesBlockValid(Arrays.asList(creature1), Collections.emptyList()));
    }

    @Test
    public void attackOrBlockHasDuplicateCreatures() {
        prepareAttackAndBlock();

        assertFalse(game.isCreaturesBlockValid(
                Arrays.asList(creature1, creature1),
                Arrays.asList(null, null)));

        assertFalse(game.isCreaturesBlockValid(
                Arrays.asList(creature1, creature2, creature2),
                Arrays.asList(null, null, creature3)));

        assertFalse(game.isCreaturesBlockValid(
                Arrays.asList(creature1, creature2),
                Arrays.asList(creature3, creature3)));
    }

    private void prepareAttackAndBlock() {
        prepareAttack(game.getCurrentPlayer());
        prepareAttack(game.getSecondPlayer());
    }

    private void prepareAttack(Player p) {
        for (CreatureCard c : p.getCreaturesInHand()) {
            p.putCreatureOnTable(c);
            c.unsetSummoningSickness();
        }
    }

    @Test
    public void attackOrBlockCreaturesAreNotOnTable() {
        assertFalse(game.isCreaturesBlockValid(Arrays.asList(creature1), Collections.singletonList(null)));
        prepareCreatureForAttack(creature1);
        assertFalse(game.isCreaturesBlockValid(Arrays.asList(creature1), Arrays.asList(creature3)));
    }

    @Test
    public void attackOrBlockCreaturesDoesNotBelongToPlayer() {
        assertFalse(game.isCreaturesBlockValid(
                Arrays.asList(new CreatureCardImpl("Orc", Collections.emptyList(), 1, 1)),
                Collections.singletonList(null)));

        prepareCreatureForAttack(creature1);
        assertFalse(game.isCreaturesBlockValid(
                Arrays.asList(creature1),
                Arrays.asList(new CreatureCardImpl("Orc", Collections.emptyList(), 1, 1))));
    }

    @Test
    public void blockingWithTappedCreature() {
        prepareAttackAndBlock();
        creature3.tap();

        assertFalse(game.isCreaturesBlockValid(
                Arrays.asList(creature1, creature2),
                Arrays.asList(creature4, creature3)));

    }

    @Test
    public void correctBlock() {
        prepareAttackAndBlock();

        assertTrue(game.isCreaturesBlockValid(
                Arrays.asList(creature1, creature2),
                Arrays.asList(creature4, creature3)));

        assertTrue(game.isCreaturesBlockValid(
                Arrays.asList(creature1, creature2),
                Arrays.asList(null, null)));
    }

    @Test
    public void nonBlockedCreaturesDamagePlayer() {
        prepareAttackAndBlock();
        game.performBlockAndDamage(
                Arrays.asList(creature1, creature2),
                Arrays.asList(null, null));
        assertEquals(Player.INIT_LIVES - creature1.getPower() - creature2.getPower(),
                game.getSecondPlayer().getLife());
    }


    @Test
    public void blockingCreatureShouldDie() {
        prepareAttackAndBlock();
        game.performBlockAndDamage(
                Arrays.asList(creature2),
                Arrays.asList(creature4));
        assertFalse(game.getSecondPlayer().getCreaturesOnTable().contains(creature4));
        assertTrue(game.getCurrentPlayer().getCreaturesOnTable().contains(creature2));
    }

    @Test
    public void blockedCreatureShouldDie() {
        prepareAttackAndBlock();
        game.performBlockAndDamage(
                new ArrayList<>(Arrays.asList(creature2)),
                new ArrayList<>(Arrays.asList(creature3)));
        assertFalse( game.getCurrentPlayer().getCreaturesOnTable().contains(creature2));
        assertTrue( game.getSecondPlayer().getCreaturesOnTable().contains(creature3));
    }

    @Test
    public void creatureShouldDie() {
        prepareAttackAndBlock();
        game.performBlockAndDamage(
                Arrays.asList(creature1, creature2),
            Arrays.asList(creature4, creature3));
        assertTrue( game.getCurrentPlayer().getCreaturesOnTable().contains(creature1));
        assertFalse( game.getCurrentPlayer().getCreaturesOnTable().contains(creature2));
        assertTrue( game.getSecondPlayer().getCreaturesOnTable().contains(creature3));
        assertTrue( game.getSecondPlayer().getCreaturesOnTable().contains(creature4));
    }

    @Test(expected = IllegalArgumentException.class)
    public void constructorPlayer1NullTest() {
        new GameImpl(null,new PlayerImpl("name"));
    }

    @Test(expected = IllegalArgumentException.class)
    public void constructorPlayer2NullTest() {
        new GameImpl(new PlayerImpl("name"),null);
    }
}
