package magicthegathering.impl;

import magicthegathering.game.CreatureCard;
import magicthegathering.game.ManaType;
import org.junit.Before;
import org.junit.Test;

import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.Collections;

import static org.junit.Assert.*;

/**
 * @author Zuzana Wolfova, Patrik Majerčík
 */
public class CreatureCardImplTest {

    private CreatureCard elf;

    @Before
    public void setUp() throws Exception {
        elf = new CreatureCardImpl(
                "Elf",
                Arrays.asList(ManaType.WHITE, ManaType.GREEN, ManaType.GREEN),
                2,
                1);
    }

    @Test
    public void testSummoningSickness() {
        elf.setSummoningSickness();
        assertTrue(elf.hasSummoningSickness());

        elf.unsetSummoningSickness();
        assertFalse(elf.hasSummoningSickness());
    }

    @Test
    public void totalCostIsThree() {
        assertEquals(3, elf.getTotalCost());
    }

    @Test
    public void testGetters() {
        assertEquals("Elf", elf.getName());
        assertEquals(2, elf.getPower());
        assertEquals(1, elf.getToughness());
    }

    @Test
    public void specialCostIsWhiteAndGreen() {
        assertEquals(1, elf.getSpecialCost(ManaType.WHITE));
        assertEquals(0, elf.getSpecialCost(ManaType.RED));
        assertEquals(2, elf.getSpecialCost(ManaType.GREEN));
        assertEquals(0, elf.getSpecialCost(ManaType.BLUE));
        assertEquals(0, elf.getSpecialCost(ManaType.BLACK));
    }

    @Test
    public void toStringMessage() {
        elf.setSummoningSickness();
        assertEquals("Elf [WHITE, GREEN, GREEN] 2 / 1", elf.toString());
        elf.unsetSummoningSickness();
        assertEquals("Elf [WHITE, GREEN, GREEN] 2 / 1 can attack", elf.toString());
        elf.tap();
        assertEquals("Elf [WHITE, GREEN, GREEN] 2 / 1 can attack TAPPED", elf.toString());
        elf.setSummoningSickness();
        assertEquals("Elf [WHITE, GREEN, GREEN] 2 / 1 TAPPED", elf.toString());
    }

    @Test(expected = IllegalArgumentException.class)
    public void contructorWithNameNullTest(){
        new CreatureCardImpl(null,Collections.emptyList(),1,1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void contructorWithManaCostNullTest(){
        new CreatureCardImpl("Fero",null,1,1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void contructorWithPowerNegativeTest(){
        new CreatureCardImpl("Fero",Collections.emptyList(),-1,1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void contructorWithToughnessNegativeTest(){
        new CreatureCardImpl("Fero",Collections.emptyList(),1,-11);
    }

    @Test(expected = IllegalArgumentException.class)
    public void contructorWithToughnessNegative2Test(){
        new CreatureCardImpl("Fero",Collections.emptyList(),1,0);
    }

    @Test(expected = IllegalArgumentException.class)
    public void contructorNameEmptyTest(){
        new CreatureCardImpl("",Collections.emptyList(),1,0);
    }

    @Test
    public void equalsTest() {
        assertEquals(new CreatureCardImpl("Elf",Collections.emptyList(),1,1),
                new CreatureCardImpl("Elf",Collections.emptyList(),1,1));

        assertNotEquals(new CreatureCardImpl("Non-Elf",Collections.emptyList(),1,1),
                new CreatureCardImpl("Elf",Collections.emptyList(),2,1));

        assertEquals(new CreatureCardImpl("Elf",Arrays.asList(ManaType.WHITE, ManaType.GREEN, ManaType.GREEN),1,1),
                new CreatureCardImpl("Elf",Arrays.asList(ManaType.WHITE, ManaType.GREEN, ManaType.GREEN),1,1));

        assertNotEquals(new CreatureCardImpl("Elf",Arrays.asList(ManaType.WHITE, ManaType.GREEN, ManaType.GREEN),1,1),
                new CreatureCardImpl("Elf",Arrays.asList(ManaType.WHITE, ManaType.GREEN),1,1));
    }


}
