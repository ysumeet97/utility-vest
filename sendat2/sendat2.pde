import processing.serial.*;
import java.util.*;
import java.text.*;
import java.io.FileNotFoundException;
import java.io.FileReader;
import weka.core.*;
import weka.core.Attribute;
import weka.core.DenseInstance;
import weka.classifiers.Classifier;
import weka.classifiers.lazy.IBk;
import weka.core.Instance;
import weka.core.Instances;

Serial myport;
PrintWriter output;
BufferedReader br;
ArrayList<Attribute> atts;
ArrayList<String> classval;
String a,b,c;
int a1,b1,c1;

void setup()
{
  String portname = Serial.list()[0];
  myport = new Serial(this,portname,9600);
  output = createWriter("d1.csv");
  myport.bufferUntil(10);
  a = "Safe-Zone";
  b = "Danger-Zone-I";
  c = "Danger-Zone-II";
  a1 = 0;
  b1 = 1;
  c1 = 2;
}

void draw()
{

}
void serialEvent(Serial p)
{
  try
  {
    String buffer = new String();
    buffer = p.readString();
    int val[] = new int[3];
    val = int(split(buffer,','));
    output.print(val[0]+",");
    output.print(val[1]+",");
    output.println(val[2]+",");
    
   print(val[0]+",");
    print(val[1]+",");
   print(val[2]+",:");
   br = createReader("data.arff");
    Instances data = new Instances(br);
    data.setClassIndex(data.numAttributes()-1);
    
    Classifier ibk = new IBk();
    ibk.buildClassifier(data);
    
    atts = new ArrayList<Attribute>();
    classval = new ArrayList<String>();
    classval.add("Safe-Zone");
    classval.add("Danger-Zone-I");
    classval.add("Danger-Zone-II"); 
    
    atts.add(new Attribute("Gas sensor"));
    atts.add(new Attribute("Temperature sensor"));
    atts.add(new Attribute("Heart rate sensor"));
    atts.add(new Attribute("class",classval));
    
    Instances dataRaw = new Instances("TestInstance",atts,0);
    dataRaw.setClassIndex(dataRaw.numAttributes()-1);
    
    double[] instanceValue1 = new double[dataRaw.numAttributes()];
    instanceValue1[0] = (double)val[0];
    instanceValue1[1] = (double)val[1];
    instanceValue1[2] = (double)val[2];
    instanceValue1[3] = -1;
    
    DenseInstance di = new DenseInstance(1.0,instanceValue1);
    dataRaw.add(di);
    
    double class1 = ibk.classifyInstance(dataRaw.firstInstance());
    print("instance classified as : ");
    String s1 = data.classAttribute().value((int)class1);
    println(s1);
    
    if(s1.equals(a))
    {
      p.write('0');
    }
    else if(s1.equals(b))
    {
      p.write('1');
    }
    else if(s1.equals(c))
    {
      p.write('2');
    }
  }catch(Exception e){}
 
}
void keyPressed() 
{
  output.flush(); 
  output.close();
  exit(); 
}