package converter;

import java.io.File;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;
import javax.imageio.ImageIO;

public class AnimationConverter {

    public static void main(String[] args) throws IOException{
        String path;

        System.out.print("Enter path for conversion\n>>> ");

        Scanner pathIn = new Scanner(System.in);
        //path = pathIn.next();
        path = "test.bmp";
        System.out.print("\n");



        File imageFile = new File(path);
        BufferedImage image = ImageIO.read(imageFile);
        ArrayList<Integer> serializedAnimation = new ArrayList<>();

        String lit;
        int state;

        for(int frame = 0; frame < (image.getWidth()/8); frame++) {
            for (int y = 0; image.getHeight() > y; y++) {
                for (int x = 0; 8 > x; x++) {
                    if (image.getRGB((x + (8 * frame)), y) > -16777216) {
                        lit = "░";
                        state = 0;
                    } else {
                        lit = "▓";
                        state = 1;
                    }
                    System.out.print(lit);
                    serializedAnimation.add(state);
                }
                System.out.print("\n");
            }
            System.out.print("\n");
        }

        System.out.println(serializedAnimation.toString());


        StringBuilder output = new StringBuilder();

        while(!serializedAnimation.isEmpty()) {

            StringBuilder number = new StringBuilder();
            for (int i = 0; i < 8; i++) {

                if (!serializedAnimation.isEmpty()) {
                    number.append(serializedAnimation.remove(0));
                }

            }
            output.append(Integer.parseInt(number.toString(), 2));

            if (!serializedAnimation.isEmpty()) {
                output.append(", ");
            }


        }
        System.out.println("unsigned int[] test = {" + output+ "} ;");


    }




}
