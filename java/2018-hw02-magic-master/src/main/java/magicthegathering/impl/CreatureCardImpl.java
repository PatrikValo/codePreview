package magicthegathering.impl;

import java.util.List;
import java.util.Objects;
import magicthegathering.game.AbstractCard;
import magicthegathering.game.CreatureCard;
import magicthegathering.game.ManaType;

/**
 *
 * @author Patrik Valo
 */
public class CreatureCardImpl extends AbstractCard implements CreatureCard{
    
    private String name;
    private List<ManaType> cost;
    private int power;
    private int toughness;
    private boolean summoningSickness = true;
    
    /**
     * Constructor of CreatureCardImpl
     * @param name - name of creature
     * @param cost - cost of creature
     * @param power - power of creature
     * @param toughness - toughness of creature
     */
    public CreatureCardImpl(String name, List<ManaType> cost, int power, int toughness) {
        if (name == null || name.isEmpty()) {
            throw new IllegalArgumentException("Invalid name");
        }
        if (cost == null) {
            throw new IllegalArgumentException("Invalid cost");
        }
        if (power < 0) {
            throw new IllegalArgumentException("Invalid power");
        }
        if (toughness <= 0) {
            throw new IllegalArgumentException("Invalid toughness");
        }
        
        this.name = name;
        this.power = power;
        this.cost = cost;
        this.toughness = toughness;
    }
    

    @Override
    public int getTotalCost() {
        return cost.size();
    }

    @Override
    public int getSpecialCost(ManaType mana) {
        
        int specialCost = 0;
        
        for (ManaType m : cost) {
            if (m == mana) {
                specialCost++;
            }
        }
        return specialCost;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public int getPower() {
        return power;
    }

    @Override
    public int getToughness() {
        return toughness;
    }

    @Override
    public boolean hasSummoningSickness() {
        return summoningSickness;
    }

    @Override
    public void setSummoningSickness() {
        summoningSickness = true;
    }

    @Override
    public void unsetSummoningSickness() {
        summoningSickness = false;
    }
    
    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        builder.append(name);
        builder.append(" ");
        builder.append(cost.toString());
        builder.append(" ");
        builder.append(power);
        builder.append(" / ");
        builder.append(toughness);
        if (!summoningSickness) {
            builder.append(" can attack");
        }
        if (isTapped()) {
            builder.append(" TAPPED");
        }
        return builder.toString();
    }
    
    @Override
    public boolean equals(Object o) {
        if(o.getClass() == getClass() && o != null) {
            CreatureCardImpl creature = (CreatureCardImpl) o;
            return name.equals(creature.name) &&
                    cost.equals(creature.cost) &&
                    power == creature.power &&
                    toughness == creature.toughness;
        }
        return false;
    }

    @Override
    public int hashCode() {
        int hash = 7;
        hash = 41 * hash + Objects.hashCode(this.name);
        hash = 41 * hash + Objects.hashCode(this.cost);
        hash = 41 * hash + this.power;
        hash = 41 * hash + this.toughness;
        return hash;
    }
    
}
