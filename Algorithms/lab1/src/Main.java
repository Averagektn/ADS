import java.util.Scanner;

public class Main {
    static int V = 0, H = 1, F = 2, ESCAPE_F = 0, ESCAPE_H = 6, ESCAPE_V = 11, SIZE_V = 13, SIZE_H = 13, FLOORS = 3;
    static final String RESET  = "\u001b[0m";
    static final String BLACK  = "\u001b[30m";
    static final String RED    = "\u001b[31m";
    static final String GREEN  = "\u001b[32m";
    static final String YELLOW = "\u001b[33m";
    static final String BLUE   = "\u001b[34m";
    static final String PURPLE = "\u001b[35m";
    static final String CYAN   = "\u001b[36m";
    static final String WHITE  = "\u001b[37m";

    static int goUp(char[][] a, int x, int y){
        if (a[y - 1][x] == 'X'){
            System.out.println(RED + "You can't go there");
        }
        else {
            a[y][x] = ' ';
            y--;
            a[y][x] = '*';
        }
        return y;
    }

    static int goDown(char[][] a, int x, int y){
        if (a[y + 1][x] == 'X'){
            System.out.println(RED + "You can't go there");
        }
        else {
            a[y][x] = ' ';
            y++;
            a[y][x] = '*';
        }
        return y;
    }

    static int goLeft(char[][] a, int x, int y){
        if (a[y][x - 1] == 'X'){
            System.out.println(RED + "You can't go there");
        }
        else {
            a[y][x] = ' ';
            x--;
            a[y][x] = '*';
        }
        return x;
    }

    static int goRight(char[][] a, int x, int y){
        if (a[y][x + 1] == 'X'){
            System.out.println(RED + "You can't go there");
        }
        else {
            a[y][x] = ' ';
            x++;
            a[y][x] = '*';
        }
        return x;
    }

    static void Output(char[][] a, String color){
        for (char[] chars : a) {
            for (int j = 0; j < a.length; j++)
                System.out.print(color + chars[j] + " ");
            System.out.println();
        }
        System.out.println();
    }

    static int goLift(char[][] a, int x, int y, int fl, boolean[] floor){
        Scanner scanner = new Scanner(System.in);
        char act;
        boolean isLift = (a[x + 1][y + 1] == 'L' || a[x - 1][y - 1] == 'L' || a[x - 1][y + 1] == 'L' || a[x + 1][y - 1] == 'L');

        if (isLift){
            System.out.println(RESET + "You can use lift");
            System.out.println(RESET + "Press 1 to stay on this floor");
            if (fl != 0)
                System.out.println(RESET + "Press s to go down");
            if (fl != 2)
                System.out.println(RESET + "Press w to go up");
            act = scanner.next(".").charAt(0);
            switch (act) {
                case ('s') -> {
                    floor[fl] = false;
                    fl--;
                    floor[fl] = true;
                    a[x][y] = ' ';
                }
                case ('w') -> {
                    floor[fl] = false;
                    fl++;
                    floor[fl] = true;
                    a[x][y] = ' ';
                }
            }
        }
        return fl;
    }

    static void randomSpawn(int[] pos){
            pos[V] = (int) (Math.random() * (SIZE_V - 3) + 1);
            pos[H] = (int) (Math.random() * (SIZE_H - 3) + 1);
            pos[F] = (int) (Math.random() * (FLOORS - 1) + 1);
    }

    static void Move(char[][] floor, int[] pos, boolean[] exit, String col, int[] e) {
        int tmp = pos[F];
        char act;
        Scanner scanner = new Scanner(System.in);
        while (exit[pos[F]] && tmp == pos[F]){
            if (pos[F] == e[F] && pos[H] == e[H] && pos[V] == e[V]) {
                break;
            }
            System.out.println(RESET + "To go up enter w");
            System.out.println(RESET + "To go down enter s");
            System.out.println(RESET + "To go left enter a");
            System.out.println(RESET + "To go right enter d");
            act = scanner.next(".").charAt(0);
            switch (act) {
                case ('w') -> {
                    pos[V] = goUp(floor, pos[H], pos[V]);
                    Output(floor, col);
                    pos[F] = goLift(floor, pos[H], pos[V], pos[F], exit);
                }
                case ('s') -> {
                    pos[V] = goDown(floor, pos[H], pos[V]);
                    Output(floor, col);
                    pos[F] = goLift(floor, pos[H], pos[V], pos[F], exit);
                }
                case ('a') -> {
                    pos[H] = goLeft(floor, pos[H], pos[V]);
                    Output(floor, col);
                    pos[F] = goLift(floor, pos[H], pos[V], pos[F], exit);
                }
                case ('d') -> {
                    pos[H] = goRight(floor, pos[H], pos[V]);
                    Output(floor, col);
                    pos[F] = goLift(floor, pos[H], pos[V], pos[F], exit);
                }
            }
        }
    }

    static void randomGenerate(char[][] a){
        int tmp;
        for (int i = 2; i < SIZE_V - 2; i++)
            for (int j = 2; j < SIZE_H - 2; j++)
                a[i][j] = 'X';

        a[1]                  [1] = ' ';
        a[2]                  [1] = ' ';
        a[1]         [SIZE_H - 2] = ' ';
        a[2]         [SIZE_H - 2] = ' ';
        a[SIZE_V - 2]         [1] = ' ';
        a[SIZE_V - 3]         [1] = ' ';
        a[SIZE_V - 2][SIZE_H - 2] = ' ';
        a[SIZE_V - 3][SIZE_H - 2] = ' ';

        for (int i = 1; i < SIZE_V - 2; i++) {
            tmp = (int) (Math.random() * SIZE_H - 4);
            for (int j = 1; j < 2 + tmp; j++)
                a[i][j] = ' ';
        }
        for (int j = 1; j < SIZE_V - 2; j++) {
            tmp = (int) (Math.random() * SIZE_H - 4);
            for (int i = 1; i < 2 + tmp; i++)
                a[i][j] = ' ';
        }
    }

    static void makeRandomExit(char[][][] a, int[] e){
        boolean randomized = true;
        e[V] = SIZE_V - 2;
        do {
            e[F] = (int)(Math.random()*FLOORS - 1);
            e[H] = (int)(Math.random()*8) + 2;

            if (a[e[F]][e[V]][e[H]] == ' ')
                a[e[F]][e[V] + 1][e[H]] = 'E';
            else
                randomized = false;
        }while(!randomized);

    }

    public static void main(String[] args) {

        char[][] floor_1 = {{'L','X','X','X','X','X','X','X','X','X','X','X','L'},
                            {'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X'},
                            {'X',' ','X',' ','X','X','X','X',' ','X','X',' ','X'},
                            {'X',' ','X',' ','X','X','X','X',' ',' ',' ',' ','X'},
                            {'X',' ','X',' ','X','X','X','X','X','X',' ',' ','X'},
                            {'X',' ','X',' ',' ',' ',' ','X','X','X',' ',' ','X'},
                            {'X',' ','X','X','X','X',' ','X','X','X','X',' ','X'},
                            {'X',' ','X','X','X','X',' ','X','X','X','X',' ','X'},
                            {'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X'},
                            {'X',' ','X','X','X','X',' ','X','X','X','X',' ','X'},
                            {'X',' ','X','X','X','X',' ','X','X','X','X',' ','X'},
                            {'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X'},
                            {'L','X','X','X','X','X','X','X','X','X','X','X','L'},};

        char[][] floor_2 = {{'L','X','X','X','X','X','X','X','X','X','X','X','L'},
                            {'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X'},
                            {'X',' ','X','X','X','X',' ','X','X','X','X',' ','X'},
                            {'X',' ','X','X','X','X',' ','X','X','X','X',' ','X'},
                            {'X',' ','X','X','X','X',' ','X','X','X','X',' ','X'},
                            {'X',' ',' ',' ',' ',' ',' ','X','X','X','X',' ','X'},
                            {'X',' ','X','X','X','X',' ','X','X','X','X',' ','X'},
                            {'X',' ','X','X','X','X',' ','X','X','X','X',' ','X'},
                            {'X',' ','X','X','X','X',' ','X','X','X','X',' ','X'},
                            {'X',' ','X','X','X','X',' ',' ',' ',' ',' ',' ','X'},
                            {'X',' ','X','X','X','X','X',' ','X','X','X',' ','X'},
                            {'X',' ',' ',' ','X','X','X',' ',' ',' ',' ',' ','X'},
                            {'L','X','X','X','X','X','X','X','X','X','X','X','L'},};

        char[][] floor_3 = {{'L','X','X','X','X','X','X','X','X','X','X','X','L'},
                            {'X',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','X'},
                            {'X',' ','X','X',' ','X',' ','X','X','X','X',' ','X'},
                            {'X',' ','X','X',' ','X',' ','X','X','X','X',' ','X'},
                            {'X',' ','X','X','X','X',' ','X',' ','X','X',' ','X'},
                            {'X',' ',' ',' ',' ',' ',' ',' ',' ','X','X',' ','X'},
                            {'X',' ','X','X','X','X',' ','X','X','X','X',' ','X'},
                            {'X',' ','X','X','X','X',' ','X','X','X','X',' ','X'},
                            {'X',' ','X','X','X','X',' ','X',' ',' ',' ',' ','X'},
                            {'X',' ',' ',' ',' ',' ',' ','X','X','X','X',' ','X'},
                            {'X',' ','X',' ','X','X',' ','X',' ','X','X',' ','X'},
                            {'X',' ',' ',' ','X','X','X','X',' ',' ',' ',' ','X'},
                            {'L','X','X','X','X','X','X','X','X','X','X','X','L'},};

        char[][][] floors = {floor_1,floor_2,floor_3};
        String[] colors = {BLACK, WHITE, GREEN};
        int[] position = {5,6,2}, escape = {ESCAPE_V,ESCAPE_H,ESCAPE_F};
        boolean[] isExit = {false, false, false};
        boolean gameOver = false;

        do {
            randomSpawn(position);
        }while(floors[position[F]][position[V]][position[H]] != ' ');

        isExit[position[F]] = true;

        randomGenerate(floor_1);
        randomGenerate(floor_2);
        randomGenerate(floor_3);
        makeRandomExit(floors,escape);
        Output(floor_1, BLACK);
        Output(floor_2, WHITE);
        Output(floor_3, GREEN);

        while (!gameOver) {
            floors[position[F]][position[V]][position[H]] = '*';
            Output(floors[position[F]], colors[position[F]]);
            Move(floors[position[F]], position, isExit, colors[position[F]], escape);
            if ((position[V] == escape[V]) && (position[H] == escape[H]) && (position[F] == escape[F])) {
                gameOver = true;
                System.out.println(RESET  + "VICTORY!");
                System.out.println(BLACK  + "VICTORY!");
                System.out.println(RED    + "VICTORY!");
                System.out.println(GREEN  + "VICTORY!");
                System.out.println(YELLOW + "VICTORY!");
                System.out.println(BLUE   + "VICTORY!");
                System.out.println(PURPLE + "VICTORY!");
                System.out.println(CYAN   + "VICTORY!");
                System.out.println(WHITE  + "VICTORY!");
            }

        }

    }

}