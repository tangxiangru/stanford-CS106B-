/* 
 * TODO: put your own comments here. Also you should leave comments on
 * each of your methods.
 */
#include <math.h>
#include "recursion.h"
#include "map.h"
#include "vector.h"
#include "set.h"
#include "gwindow.h"
#include "gobjects.h"
#include "tokenscanner.h"
using namespace std;


int gcd(int a, int b);
void serpinskii(GWindow &w, int leftX, int leftY, int size, int order);
double getHeight(double a, double b);
void drawSerpinskiiTriangles(GWindow &w, double leftX, double leftY, double size, double order);
void drawTriangle(GWindow &w, double leftX, double leftY, double size);
int floodFill(GBufferedImage &image, int x, int y, int color);
int doFloodFill(GBufferedImage &image, int x, int y, int newColor, int originalColor);
void personalCurriculum(Map<string, Vector<string> > &prereqMap, string goal);
void doCurriculum(Map<string, Vector<string> > &prereqMap, string goal, Set<string> &printed);
string generate(Map<string, Vector<string> > &grammar, string symbol);
string getRandom(Vector<string> vector);
void doGenerate(Map<string, Vector<string> > &grammar, string symbol, string &sentence);



int gcd(int a, int b) {
    // your code here
    if(a%b == 0){
        cout << "gcd(" << a << ", " << b << ") = " << b << endl;
        return b;
    }else{
        cout << "gcd(" << a << ", " << b << ") = gcd(" << b << ", " << a % b << ")" << endl;
        return gcd(b, a%b);
    }
}





void serpinskii(GWindow &w, int leftX, int leftY, int size, int order) {
        double mleftX = leftX;
        double mleftY = leftY;
        double mSize = size;
        drawSerpinskiiTriangles(w, mleftX, mleftY, mSize, order);
}


double getHeight(double c, double a) {
    return sqrt(c * c - a * a);
}

void drawSerpinskiiTriangles(GWindow &w, double leftX, double leftY, double size, double order){
   if(order == 0){
       drawTriangle(w, leftX, leftY, size);
   }else{
       order--;
       double halfSize = size/2;
       double height = getHeight(halfSize, halfSize/2);
       drawSerpinskiiTriangles(w, leftX, leftY, halfSize, order);
       drawSerpinskiiTriangles(w, leftX + halfSize, leftY, halfSize, order);
       drawSerpinskiiTriangles(w, leftX + halfSize/2, leftY + height, halfSize, order);
   }
}

void drawTriangle(GWindow &w, double leftX, double leftY, double size) {
   double height = getHeight(size, size / 2);
   double rightX = leftX + size;
   double bottomY = leftY + height;
   double bottomX = leftX + size/2;

   w.drawLine(leftX, leftY, rightX, leftY);
   w.drawLine(leftX, leftY, bottomX, bottomY);
   w.drawLine(rightX, leftY, bottomX, bottomY);
}










int floodFill(GBufferedImage& image, int x, int y, int newColor) {
    int originalColor = image.getRGB(x, y);

    if(originalColor == newColor){
        return 0;
    }
   return doFloodFill(image, x, y, newColor, originalColor);
}

int doFloodFill(GBufferedImage& image, int x, int y, int newColor, int originalColor){
    int number;

    if (image.inBounds(x, y) && image.getRGB(x, y) == originalColor) {
        image.setRGB(x, y, newColor);
        number++;
        doFloodFill(image, x+1, y, newColor, originalColor);
        doFloodFill(image, x-1, y, newColor, originalColor);
        doFloodFill(image, x, y+1, newColor, originalColor);
        doFloodFill(image, x, y-1, newColor, originalColor);
        }
        return number;
}



void personalCurriculum(Map<string, Vector<string>> & prereqMap,string goal) {
    Set<string> printed;
    doCurriculum(prereqMap, goal, printed);
}

void doCurriculum(Map<string, Vector<string> > & prereqMap, string goal, Set<string> & printed){
    if(prereqMap.containsKey(goal)){
        for(string item: prereqMap[goal]){
            doCurriculum(prereqMap, item, printed);
        }
    }
    if(!printed.contains(goal)){
        cout << goal << endl;
        printed.add(goal);
    }
}





string generate(Map<string, Vector<string> > & grammar, string symbol) {
    string sentence;
    doGenerate(grammar, symbol, sentence);
    return sentence;
}


string getRandom(Vector<string> vector){
    int index = randomInteger(0,vector.size() - 1);
    return vector[index];
}

void doGenerate(Map<string, Vector<string> > & grammar, string symbol, string & sentence)
{
    if(!grammar.containsKey(symbol)){
        sentence += symbol;
    }
    else
    {
        string nextOption = getRandom(grammar[symbol]);
        TokenScanner scanner(nextOption);
        while(scanner.hasMoreTokens()){
            string nextSymbol = scanner.nextToken();
            doGenerate(grammar, nextSymbol, sentence);
        }
    }
}
