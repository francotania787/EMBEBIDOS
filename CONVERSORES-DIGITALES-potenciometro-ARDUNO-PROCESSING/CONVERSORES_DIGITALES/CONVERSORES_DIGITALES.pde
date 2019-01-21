import controlP5.*;
ControlP5 cp5;
import processing.serial.*;
Serial port;
Chart myChart;
String dato;
float valor;
float pot;

void setup(){
size(1200,600);
background(214, 247, 245);
port = new Serial (this, "COM4",9600);
cp5 = new ControlP5(this);

textSize(35);
fill(15, 21, 74);
textAlign(CENTER);
text("CONVERSORES DIGITALES", 600, 30);

textSize(25);
fill(15, 21, 74);
textAlign(CENTER);
text("Gráfica voltaje - tiempo", 805, 80);
textSize(25);
fill(15, 21, 74);
textAlign(CENTER);
text("Potenciómetro", 200,400 );
textSize(23);
fill(15, 90, 80);
textAlign(CORNER);
text("Integrantes:", 30,520 );
textSize(20);
fill(15, 90, 80);
text("Franco Tania", 60,550 );
text("Noboa Esteban", 60,570 );
text("Rivera Diana", 60,590 );

cp5 = new ControlP5(this);
  myChart = cp5.addChart("dataflow")
               .setPosition(575, 100)
               .setSize(500, 350)
               .setRange(0, 100)
               .setView(Chart.BAR_CENTERED) // use Chart.LINE, Chart.PIE, Chart.AREA, Chart.BAR_CENTERED
               .setStrokeWeight(100)
               .setColorCaptionLabel(color(255))
               ;

  myChart.addDataSet("incoming");
  myChart.setData("incoming", new float[100]);
  }

void draw(){
while(port.available()>0){
  dato = port.readString();
    if(dato==null){println("FALLO");}
    else if(dato!=null){
     valor = PApplet.parseFloat(dato);
     pot = PApplet.parseInt(valor);
    }
    
  cp5.addSlider("pot") //barra horrizontal
    .setPosition(5,200)
    .setSize(400,100)
    .setRange(0,100) //da valores por pixel
    .setColorBackground(color(58,88,172))
    .setColorActive(color(255,201,71)) //cuando se activa el maus
    .setColorForeground(color(202,209,214)) //para cuando se quita el maus
    .setValue(valor); //donde inicia'
}  myChart.push("incoming", ((valor)));
}

public void pot(float valorP){
valorP=pot;
  println(valorP);
}