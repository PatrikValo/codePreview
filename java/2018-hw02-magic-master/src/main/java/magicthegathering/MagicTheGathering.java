package magicthegathering;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;
import magicthegathering.game.Card;
import magicthegathering.game.CreatureCard;
import magicthegathering.game.Game;
import magicthegathering.game.LandCard;
import magicthegathering.game.Player;


import magicthegathering.impl.GameImpl;
import magicthegathering.impl.PlayerImpl;

/**
 * This is the main class containing text user interface and logic for the game.
 *
 * @author Zuzana Wolfova, Patrik Majerčík
 */
public class MagicTheGathering {

    private static final int SKIP = -42;
    private static final int NULL_CREATURE = -1;

    private static final Scanner READER = new Scanner(System.in);
    private static Game game;

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        System.out.println("Welcome to Magic the Gathering!");
        System.out.println("Empty line means skipping the action.");

        Player[] players = getPlayersName();
        game = new GameImpl(players[0], players[1]);
        game.initGame();

        while (!isPlayerDead()) {
            playTurn();
            game.changePlayer();
        }

        System.out.println("Player " + game.getSecondPlayer() + " has won.");
    }

    private static Player[] getPlayersName() {
        Player[] players = new Player[2];
        for (int i = 0; i < players.length; i++) {
            System.out.println("Enter name for player " + (i + 1));
            players[i] = new PlayerImpl(READER.nextLine());
        }
        return players;
    }

    private static boolean isPlayerDead() {
        return game.getCurrentPlayer().isDead();
    }

    private static void playTurn() {

        System.out.println();
        System.out.println("Turn of Player " + game.getCurrentPlayer().getName() + " with life "
                + game.getCurrentPlayer().getLife() + " begins.");
        System.out.println("===========================================================");
        System.out.println();
        game.prepareCurrentPlayerForTurn();

        System.out.println("Your hand:");
        System.out.println();
        game.getCurrentPlayer().getCardsInHand().stream().forEach(System.out::println);
        System.out.println();

        System.out.println("Your table:");
        System.out.println();
        game.getCurrentPlayer().getCardsOnTable().stream().forEach(System.out::println);
        System.out.println();

        putLandOnTable();
        buyCreatures();
        performAttackAndBlock();
    }

    private static void putLandOnTable() {
        System.out.println("Phase 1 - putting land on the table");
        System.out.println("===================================");
        System.out.println();

        List<LandCard> landsInHand = game.getCurrentPlayer().getLandsInHand();
        printCardsWithIndexes(new ArrayList<>(landsInHand));

        System.out.println("Which land you want to put on the table?");

        int landIndex = readIntLine();
        if (landIndex < 0 || landIndex >= landsInHand.size()) {
            System.out.println("Invalid index, skipping.");
            return;
        }

        game.getCurrentPlayer().putLandOnTable(landsInHand.get(landIndex));
    }

    private static void buyCreatures() {
        System.out.println("Phase 2 - putting creatures on the table");
        System.out.println("========================================");
        System.out.println();

        List<CreatureCard> creaturesInHand = game.getCurrentPlayer().getCreaturesInHand();

        System.out.println("Lands on table:");
        game.getCurrentPlayer().getLandsOnTable().stream().forEach(System.out::println);
        System.out.println();
        System.out.println("Creatures in hand:");
        printCardsWithIndexes(new ArrayList<>(creaturesInHand));

        while (true) {
            System.out.println("Type creature number you want to put on the table:");
            int creatureIndex = readIntLine();

            if (creatureIndex < 0 || creatureIndex >= creaturesInHand.size()) break;

            boolean put = game.getCurrentPlayer().putCreatureOnTable(creaturesInHand.get(creatureIndex));

            if (put) {
                System.out.println("Creature was put on table.");
            } else {
                System.out.println("Creature could not be put on table!");
            }
        }
    }

    private static void performAttackAndBlock() {
        List<CreatureCard> attackingCreatures = performAttack();
        performBlock(attackingCreatures);
    }

    private static List<CreatureCard> performAttack() {
        System.out.println("Phase 3.1 - choosing which creatures will attack");
        System.out.println("================================================");
        System.out.println();

        List<CreatureCard> attackingCreatures = pickCreaturesForAttack();
        while (!game.isCreaturesAttackValid(attackingCreatures)) {
            System.out.println("Invalid attack, try again.");
            attackingCreatures = pickCreaturesForAttack();
        }

        game.performAttack(attackingCreatures);
        return attackingCreatures;
    }

    private static void performBlock(List<CreatureCard> attackingCreatures) {
        System.out.println("Phase 3.2 - choosing which creatures will block");
        System.out.println("Note: -1 represents that creature is not blocked");
        System.out.println("================================================");
        System.out.println();

        if (attackingCreatures.size() == 0) {
            System.out.println("Skipping action.");
            return;
        }

        List<CreatureCard> blockingCreatures = pickCreaturesForBlock(attackingCreatures);
        while (!game.isCreaturesBlockValid(attackingCreatures, blockingCreatures)) {
            System.out.println("Invalid block, try again.");
            blockingCreatures = pickCreaturesForBlock(attackingCreatures);
        }

        printBlock(attackingCreatures, blockingCreatures);
        game.performBlockAndDamage(attackingCreatures, blockingCreatures);
    }

    private static void printBlock(List<CreatureCard> attackingCreatures, List<CreatureCard> blockingCreatures) {
        System.out.println("Block: ");
        for (int i = 0; i < attackingCreatures.size(); i++) {
            String blockingOne = blockingCreatures.get(i) == null ? "PLAYER" : blockingCreatures.get(i).toString();
            System.out.println(attackingCreatures.get(i) + " -> " + blockingOne);
        }
    }

    private static List<CreatureCard> pickCreaturesForAttack() {
        return pickCreaturesFor(true);
    }

    private static List<CreatureCard> pickCreaturesForBlock(List<CreatureCard> attackingCreatures) {
        List<CreatureCard> blockCreatures = pickCreaturesFor(false);
        if (blockCreatures.size() == 0) {
            blockCreatures = new ArrayList<>();
            while (blockCreatures.size() < attackingCreatures.size()) {
                blockCreatures.add(null);
            }
        }
        return blockCreatures;
    }

    private static List<CreatureCard> pickCreaturesFor(boolean isAttack) {
        String action = isAttack ? "attack" : "block";
        Player playersCreatures = isAttack ? game.getCurrentPlayer() : game.getSecondPlayer();

        List<CreatureCard> creaturesOnTable = playersCreatures.getCreaturesOnTable();

        if (creaturesOnTable.size() == 0) {
            System.out.println("Skipping action.");
            return Collections.emptyList();
        }

        return processActionInput(creaturesOnTable, action);
    }

    private static List<CreatureCard> processActionInput(List<CreatureCard> creaturesOnTable, String action) {
        while (true) {
            System.out.println("Choose creatures for " + action + " (whitespace separated numbers):");
            printCardsWithIndexes(new ArrayList<>(creaturesOnTable));

            String answer = READER.nextLine();

            String[] creaturesForAction = answer.split("\\s+");
            List<CreatureCard> creatures = new ArrayList<>();
            int i;
            for (i = 0; i < creaturesForAction.length; i++) {
                int index = parseInt(creaturesForAction[i]);
                if (index >= 0 && index < creaturesOnTable.size()) {
                    creatures.add(i, creaturesOnTable.get(index));
                } else {
                    if (index == SKIP) {
                        return Collections.emptyList();
                    } else if (index == NULL_CREATURE) {
                        creatures.add(i,null);
                    } else {
                        System.out.println("Invalid index " + index + ", try again");
                        break;
                    }
                }
            }
            if (i == creaturesForAction.length) {
                return creatures;
            }
        }
    }

    private static int readIntLine() throws NumberFormatException {
        return parseInt(READER.nextLine());

    }

    private static int parseInt(String inputString) throws NumberFormatException {
        if (inputString.trim().isEmpty()) return SKIP;
        return Integer.parseInt(inputString);
    }

    private static void printCardsWithIndexes(List<Card> cards) {
        for (int i = 0; i < cards.size(); i++) {
            System.out.println(i + ": " + cards.get(i));
        }
        System.out.println();
    }

}
