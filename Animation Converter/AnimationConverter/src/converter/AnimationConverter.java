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
        path = "test2.bmp";
        System.out.print("\n");



        File imageFile = new File(path);
        BufferedImage image = ImageIO.read(imageFile);

        serializeFrames(image);

        serializeScrollingAnimation(image);


    }

    private static void serializeScrollingAnimation(BufferedImage image){
        ArrayList<Integer> serializedAnimation = new ArrayList<>();

        String lit;
        int state;
        int counter = 0;

        for(int x=0;x<image.getWidth();x++){
            for(int y=0;y<image.getHeight();y++){
                if (image.getRGB(x, y) > -16777216) {
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

        System.out.println(serializedAnimation.toString());

        StringBuilder output = new StringBuilder();

        while(!serializedAnimation.isEmpty()){
            StringBuilder number = new StringBuilder();

            for (int i = 0; i < 6; i++) {

                if (!serializedAnimation.isEmpty()) {
                    number.append(serializedAnimation.remove(0));
                }

            }
            output.append(Integer.parseInt(number.toString(), 2));

            counter++;

            if (!serializedAnimation.isEmpty()) {
                output.append(", ");
            }

        }
        System.out.println("Scrolling Animation: const unsigned int frameAnimation[] = {" + output+ "} ;");
        System.out.println("Scrolling Animation: const int animationLength = " + counter+ " ;");
    }

    private static void serializeFrames(BufferedImage image){
        ArrayList<Integer> serializedAnimation = new ArrayList<>();

        String lit;
        int state;
        int counter = 0;

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
            //
            for (int i = 0; i < 8; i++) {

                if (!serializedAnimation.isEmpty()) {
                    number.append(serializedAnimation.remove(0));
                }

            }
            output.append(Integer.parseInt(number.toString(), 2));

            counter++;

            if (!serializedAnimation.isEmpty()) {
                output.append(", ");
            }


        }
        System.out.println("Frame Animation:  const unsigned int frameAnimation[] = {" + output+ "} ;");
        System.out.println("Frame Animation:  const int maxFrames = " + counter/6+ " ;");
    }




}
