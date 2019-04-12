package magicthegathering.impl;

import java.util.Objects;
import magicthegathering.game.AbstractCard;
import magicthegathering.game.LandCard;
import magicthegathering.game.LandCardType;
import magicthegathering.game.ManaType;

/**
 *
 * @author Patrik Valo
 */
public class LandCardImpl extends AbstractCard implements LandCard{
    
    private LandCardType landType;
    private ManaType manaType;
    
    /**
     * Constructor of LandCardImpl
     * @param landType - type of land
     */
    public LandCardImpl(LandCardType landType) {
        if (landType == null) {
            throw new IllegalArgumentException("Invalid landType");
        }
        this.landType = landType;
        this.manaType = suitableManaType();
    }

    private ManaType suitableManaType() {
        if(landType == LandCardType.PLAINS) {
            return ManaType.WHITE;
        }
        if (landType == LandCardType.ISLAND) {
            return ManaType.BLUE;
        }
        if (landType == LandCardType.SWAMP) {
            return ManaType.BLACK;
        }
        if (landType == LandCardType.MOUNTAIN) {
            return ManaType.RED;
        }
        return ManaType.GREEN;
    }
    
    @Override
    public LandCardType getLandType() {
        return landType;
    }

    @Override
    public ManaType getManaType() {
        return manaType;        
    }
            
    @Override
    public String toString() {
        return "Land " + getLandType().toString().toLowerCase() + 
                ", " + getManaType().toString();
    }

    @Override
    public int hashCode() {
        int hash = 3;
        hash = 61 * hash + Objects.hashCode(this.landType);
        return hash;
    }
    
    @Override
    public boolean equals(Object o) {
        if(o.getClass() == getClass() && o != null) {
            LandCardImpl land = (LandCardImpl) o;
            return landType == land.landType;
        }
        return false;
    }
}
