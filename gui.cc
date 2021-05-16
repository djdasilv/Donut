// projet.cc
// Auteurs : Georg Schwabedal et Daniel Silva

#include "gui.h"
#include "graphic.h"
#include "geomod.h"
#include "simulation.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>
#include <cairomm/context.h>

using namespace std;

namespace {
	size_t count2(4);
	int DEFAULT_SIZE = 800;
	int count3(count2);
	Simulation* sim(nullptr);
	bool link2(true), range (true),started(false),step(false);
}


// Fonctions de la fenetre
Windowx::Windowx()
:	m_box(Gtk::ORIENTATION_VERTICAL),
	m_box_Bottom(Gtk::ORIENTATION_VERTICAL,5),
	m_box_Top(Gtk::ORIENTATION_HORIZONTAL,5),
	m_box_Button(Gtk::ORIENTATION_VERTICAL,5)
	
	
{
	set_title("Planet Donut");
	add(m_box);
	m_box.set_border_width(5);
	m_box.add(m_box_Top);
	m_box.add(m_box_Bottom);
	m_box_Top.add(m_box_Button);
	m_box_Button.add(m_box_General);
	m_box_Button.add(m_box_Display);
	m_box_Bottom.add(scroll);
	Area.set_size_request(taille_dessin, taille_dessin);
	
	//Ajoute les boutons de General et Toggle Display dans un box
	m_box_General.pack_start(	*Gtk::manage( new ButtonBox(false, "General", 5,
			Gtk::BUTTONBOX_SPREAD)), Gtk::PACK_EXPAND_WIDGET);
			
	m_box_Display.pack_start(*Gtk::manage( new ButtonBox2(false, "Toggle Display", 5,
			Gtk::BUTTONBOX_SPREAD)), Gtk::PACK_EXPAND_WIDGET);

	m_box_Top.add(m_Frame_Horizontal);
	//Ce frame contient la surface de dessin 
	//set_default_size(dim_max, dim_max);
	m_Frame_Horizontal.add(Area);
    m_Frame_Horizontal.set_hexpand(true); 
   
    m_Frame_Horizontal.set_halign(Gtk::ALIGN_FILL);
	m_Frame_Horizontal.set_vexpand(true);
    m_Frame_Horizontal.set_valign(Gtk::ALIGN_FILL);
  show_all_children();
  
  // updating a simulation in idle signal handler - called as quickly as possible
  Glib::signal_idle().connect( sigc::mem_fun(*this, &Windowx::on_idle));

}

Windowx::~Windowx()
{
}

bool Windowx::on_idle()
{
  static unsigned count(0);
  
  Area.refresh();
  scroll.tree_view_update();

  if(started)
  {
	cout << "Mise à jour de la simulation numéro : " << ++count << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  else if (step)
  {
	step = false;
	cout << "Mise à jour de la simulation numéro : " << ++count << endl;
  }
    
  return true;  // return false when done
}

// Fonctions du widget scroll
// ==============================================================================
// cette constante et le modèle de struct qui suit simulent les données que pourrait
// fournir le module simulation en réponse à une demande de tree_view_update()
constexpr unsigned max_tab(10);

struct SimData
{
  unsigned nbP;
  unsigned nbF;
  unsigned nbT;
  unsigned nbC;
  double ressource;
  double ressource_p;
};


// =================================


Scroll::Scroll()
     :_v_box(Gtk::ORIENTATION_VERTICAL, 10)
{
  add(_v_box);
  // This is the part for the scrolled_window
  _v_box.add(_scrolled_window);
  _scrolled_window.set_size_request(-1, 200); 
  _scrolled_window.add(_tree_view);

  _scrolled_window.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC,
							  Gtk::PolicyType::POLICY_AUTOMATIC);
  _scrolled_window.set_hexpand();

  _tree_view.append_column("nbP", _columns._col_nbP);
  _tree_view.append_column("nbF", _columns._col_nbF);
  _tree_view.append_column("nbT", _columns._col_nbT);
  _tree_view.append_column("nbC", _columns._col_nbC);
  _tree_view.append_column_numeric("Amount resource", _columns._col_resource, "%.2f");

  auto cell = Gtk::make_managed<Gtk::CellRendererProgress>();
  int cols_count = _tree_view.append_column("Mission completeness", *cell);

  auto progress_col = _tree_view.get_column(cols_count - 1);
  if(progress_col)
	progress_col->add_attribute(cell->property_value(),
								_columns._col_resource_percentage);
	
  show_all_children();
}

Scroll::~Scroll(){}


// the declaration below should not exist in your gui module; instead you should have a
// local vector declared in the method tree_view_update() and such a vector such be
// updated with the value returned by a call to your simulation module.

namespace
{
  static std::vector<SimData> report(max_tab); // init with zeros
}

// ===================== the parts to adapt have a comment ==================
void Scroll::tree_view_update()
{
  Glib::RefPtr<Gtk::ListStore> ref_tree_model = Gtk::ListStore::create(_columns);
  _tree_view.set_model(ref_tree_model);

  if(sim->simulation()) // here there should be a test about the existence of a simulation
  {
	for(size_t i = 0 ; i <sim->base_size() ; i++)
	{
	  report[i].nbP = sim->get_base(i)->get_nbP();
	  report[i].nbF = sim->get_base(i)->get_nbF();
	  report[i].nbT = sim->get_base(i)->get_nbT();
	  report[i].nbC = sim->get_base(i)->get_nbC();
	  report[i].ressource   = sim->get_base(i)->get_ressources();
	  report[i].ressource_p = report[i].ressource *100/finR;
		
	  auto row = *(ref_tree_model->append());
	  row[_columns._col_nbP] = report[i].nbP;
	  row[_columns._col_nbF] = report[i].nbF;
	  row[_columns._col_nbT] = report[i].nbT;
      row[_columns._col_nbC] = report[i].nbC;
	  row[_columns._col_resource] = report[i].ressource;
	  row[_columns._col_resource_percentage] = report[i].ressource_p;
	}
  }
}


//Fonctions de la ButtonBox contenant les boutons Exit, Save, Open, Step et Start 
ButtonBox::ButtonBox(	bool horizontal, const Glib::ustring& title,
									gint spacing,  Gtk::ButtonBoxStyle layout)
: 	Gtk::Frame(title),
	m_Button_Exit("Exit"),

	m_Button_Open("Open"),
	m_Button_Step("Step"),
	m_Button_Save("Save")

{
	Gtk::ButtonBox* bbox = nullptr;
	m_Button_Start.set_label("Start");
	bbox = Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_VERTICAL) );

	bbox->set_border_width(5);

	set_halign(Gtk::ALIGN_FILL);
	 
	add(*bbox);
	m_Button_Exit.signal_clicked().connect(sigc::mem_fun(*this, &ButtonBox::on_button_clicked_Exit) );
	m_Button_Open.signal_clicked().connect(sigc::mem_fun(*this, &ButtonBox::on_button_clicked_Open) );
	m_Button_Save.signal_clicked().connect(sigc::mem_fun(*this, &ButtonBox::on_button_clicked_Save) );
	m_Button_Start.signal_clicked().connect(sigc::mem_fun(*this, &ButtonBox::on_button_clicked_Start) );
	m_Button_Step.signal_clicked().connect(sigc::mem_fun(*this, &ButtonBox::on_button_clicked_Step) );

	/* Set the appearance of the Button Box */
	bbox->set_layout(layout);
	bbox->set_spacing(5);
	bbox->add(m_Button_Exit);
	bbox->add(m_Button_Start);
	bbox->add(m_Button_Open);
	bbox->add(m_Button_Step);
	bbox->add(m_Button_Save);
}

void ButtonBox::on_button_clicked_Exit(){
	exit(EXIT_SUCCESS);
}

void ButtonBox::on_button_clicked_Open(){
	
	Gtk::FileChooserDialog dialog(	"Please choose a file",
									Gtk::FILE_CHOOSER_ACTION_OPEN);

	//Add response buttons the the dialog:
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);
	m_Label_Info.set_text("choosing a file");
	//Show the dialog and wait for a user response:
	int result = dialog.run();

	m_Label_Info.set_text("Done choosing a file");
	 //Handle the response:
	switch(result){
		case(Gtk::RESPONSE_OK):
		{
			cout << "Open clicked." << endl;
			istringstream data(dialog.get_filename());   
			string line ;
			while (getline (data,line,'/')){}
			char argv[line.length()+1];	
			char* filename = argv;
			for (size_t i=0; i< line.length(); i++) argv[i]= line[i];
			argv[line.length()]= '\0';
			delete sim;
			cout << "File selected: " <<  line << endl;
			sim=new Simulation();
			sim->lecture(filename);	 	
			break;
		}
		case(Gtk::RESPONSE_CANCEL):{
			cout << "Cancel clicked." << endl;
			break;
		}
		default:{
			cout << "Unexpected button clicked." << endl;
			break;
		}
	}
}

void ButtonBox::on_button_clicked_Save(){
	
	Gtk::FileChooserDialog dialog(	"Please choose a file",
									Gtk::FILE_CHOOSER_ACTION_SAVE);
						
	//Add response buttons the the dialog:
	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Save", Gtk::RESPONSE_OK);
	m_Label_Info.set_text("choosing a file");
	//Show the dialog and wait for a user response:
	int result = dialog.run();

	m_Label_Info.set_text("Done choosing a file");
	 //Handle the response:
		switch(result){
		case(Gtk::RESPONSE_OK):
		{	
			cout << "Save clicked." << endl;
			istringstream data(dialog.get_filename());   
			string line ;
			while (getline (data,line,'/')){}
			char argv[line.length()+1];	
			char* filename = argv;
			for (size_t i=0; i< line.length(); i++) argv[i]= line[i];
			
			argv[line.length()]= '\0';
			saveGisement(filename);

			break;
		}
		case(Gtk::RESPONSE_CANCEL):{
			cout << "Cancel clicked." << endl;
			break;
		}
		default:{
			cout << "Unexpected button clicked." << endl;
			break;
		}
	}
}

void ButtonBox::on_button_clicked_Start(){ 
	started=not(started);
	if (started) m_Button_Start.set_label("Stop");
	else m_Button_Start.set_label("Start");
}

void ButtonBox::on_button_clicked_Step(){
	step=not(step);
}

//Fonctions de la ButtonBox contenant les boutons Toggle link et Toggle range

ButtonBox2::ButtonBox2(	bool horizontal, const Glib::ustring& title,
									gint spacing,  Gtk::ButtonBoxStyle layout)
: 	Gtk::Frame(title),
	m_Button_Link("Toggle link"),
	m_Button_Range("Toggle range")
{
	Gtk::ButtonBox* bbox2=Gtk::manage( new Gtk::ButtonBox(Gtk::ORIENTATION_VERTICAL));

	bbox2->set_border_width(1);

	add(*bbox2);
	this->set_valign(Gtk::ALIGN_FILL);
	m_Button_Link.signal_clicked().connect(sigc::mem_fun(*this, &ButtonBox2::on_button_clicked_Link) );
	m_Button_Range.signal_clicked().connect(sigc::mem_fun(*this, &ButtonBox2::on_button_clicked_Range) );

	/* Set the appearance of the Button Box */
	bbox2->set_layout(Gtk::BUTTONBOX_EXPAND);
	bbox2->set_spacing(1);
	bbox2->add(m_Button_Link);
	bbox2->add(m_Button_Range);

}

void ButtonBox2::on_button_clicked_Link(){
	link2=not (link2);
	}

void ButtonBox2::on_button_clicked_Range(){
	range=not(range);
}

//Fonctions de la DrawingArea

MyArea::MyArea(){}

MyArea::~MyArea(){}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	Gtk::Allocation allocation = get_allocation();
	const int width = allocation.get_width();
	const int height = allocation.get_height();	
	graphic_set_context(cr);
	orthographic_projection(cr,DEFAULT_SIZE, DEFAULT_SIZE);
	dessin_cadre(height,width);
	
	draw_gisements(height,width);
	draw_bases(height, width);
	cr->set_source_rgb(0,0,0);
	

	
  return true;
}

//Convertion du systeme d'axe de DrawingArea vers celle de Planet Donut
void MyArea::orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, double width, double height)
{
	double xMax(dim_max),xMin(-dim_max),yMax(dim_max),yMin(-dim_max);
	
	// déplace l'origine au centre de la fenêtre
	cr->translate(width/2, height/2);
  
	// normalise la largeur et hauteur aux valeurs fournies par le cadrage
	// ET inverse la direction de l'axe Y
	cr->scale(width/(xMax - xMin), -height/(yMax - yMin));
  
	// décalage au centre du cadrage
	cr->translate(-(xMin + xMax)/2, -(yMin +yMax)/2);
}


void MyArea::refresh()
{
  auto win = get_window();
  if(win)
  {
	  Gdk::Rectangle r(0,0, get_allocation().get_width(), 
	                        get_allocation().get_height());
	  win->invalidate_rect(r,false);
  }
}

void set_simulation(Simulation* simulation){
	sim = simulation ;
}

void saveGisement(char* filename){
	ofstream myfile;
	myfile.open (filename);
	if (sim->gisement_size()>0) myfile<<sim->gisement_size()<<"\n";
	for (size_t i(0); i< sim->gisement_size(); i++){
		myfile<<sim->get_gisement(i)->get_x()<< " ";
		myfile<<sim->get_gisement(i)->get_y()<<" ";
		myfile<<sim->get_gisement(i)->get_rayon()<<" ";
		myfile<< sim->get_gisement(i)->get_qt_resources()<<"\n";}
	if (sim->base_size()>0) myfile<<sim->base_size()<<"\n";
	saveBase(filename,myfile);
}



void saveBase(char* filename, ofstream& myfile ){
	for (size_t i(0); i< sim->base_size() ; i++){
		myfile<<sim->get_base(i)->get_x() <<" "<<sim->get_base(i)->get_y()<<" ";
		myfile<<sim->get_base(i)->get_ressources()<<" "; 
		myfile<<sim->get_base(i)->get_nbP()<<" ";
		myfile<<sim->get_base(i)->get_nbF()<<" ";
		myfile<<sim->get_base(i)->get_nbT()<<" ";
		myfile<<sim->get_base(i)->get_nbC()<<"\n";
		
		for (int j(0); j <sim->get_base(i)->get_nb_robot(); j++ ){
			myfile<<sim->get_base(i)->get_robot(j)->get_uid()<<" ";
			myfile<<sim->get_base(i)->get_robot(j)->get_compteur_de_distance ()<<" ";
			myfile<<sim->get_base(i)->get_robot(j)->get_x()<<" ";
			myfile<<sim->get_base(i)->get_robot(j)->get_y()<<" ";
			myfile<<sim->get_base(i)->get_robot(j)->get_but().get_x()<<" ";
			myfile<<sim->get_base(i)->get_robot(j)->get_but().get_y()<<" ";
			myfile<<boolToString(sim->get_base(i)->get_robot(j)->get_atteint())<<" ";
			
			if(sim->get_base(i)->get_robot(j)->get_type() == 'P' ){
				
				myfile<<boolToString(sim->get_base(i)-> get_robot(j)->get_retour());
				myfile<<" ";
				myfile<<boolToString(sim->get_base(i)-> get_robot(j)->get_found());
				
				if (sim->get_base(i)-> get_robot(j)->get_found()==true  ){
					myfile<< "true"<<sim->get_base(i)->get_robot(j)->get_xg()<<" ";
					myfile<<sim->get_base(i)-> get_robot(j)->get_yg()<<" ";
					myfile<<sim->get_base(i)-> get_robot(j)->get_rayong()<<" ";
					myfile<<sim->get_base(i)-> get_robot(j)->get_capaciteg()<< "\n";}
				
				else {myfile <<"\n";}
			
			} else if (sim->get_base(i)->get_robot(j)->get_type() == 'T'){
				
				myfile<<boolToString(sim->get_base(i)->get_robot(j)->get_retour());
				myfile<<"\n";
			
			} else if (	(sim->get_base(i)->get_robot(j)->get_type() == 'C') or 
						(sim->get_base(i)->get_robot(j)->get_type() == 'F')){
				myfile<<"\n";}
			}		
		}	
	myfile.close();
}

string boolToString(bool a){
	if(a == false) return "false";
	else return "true";
}

void draw_bases(int height, int width){
	for (size_t i(0); i<sim->base_size(); i++){ 
		
		sim->get_base(i)->get_centre().normalisation(sim->get_base(i)->get_centre());
		
		dessin_point(sim->get_base(i)->get_x(),sim->get_base(i)->get_y());
		set_couleur_base(i+1);
		dessin_base(height,width,sim->get_base(i)->get_x(),sim->get_base(i)->get_y(),
						10*rayon_base);
		//Dessine les robots
		for(int j(0);j <sim-> get_base(i)->get_nb_robot(); j++){
			dessin_point(sim->get_base(i)->get_robot(j)->get_x(),sim->get_base(i)->get_robot(j)->get_y());
			int rayon_robot(300);
			if (range and sim->get_base(i)->get_robot(j)->get_type() =='C' ){
				dessin_base(height,width,sim->get_base(i)->get_robot(j)->get_x(),sim->get_base(i)->get_robot(j)->get_y(),rayon_robot);
			}
		}

	}
	
}
void draw_gisements(int height, int width){
	//Desssine les gisements
  
	for (size_t i(0); i<sim->gisement_size(); i++){

		sim->get_gisement(i)->getCercleG().get_centre().normalisation( sim->get_gisement(i)->
																getCercleG().
																get_centre());
		dessin_gisement(height,width,sim->get_gisement(i)->get_x(), 
						sim->get_gisement(i)->get_y(), sim->get_gisement(i)->get_rayon());
	}
}
/***
void draw(int height, int width,int base){
	for(int i(0); i<sim->get_base(i))// Completer boucle pour parcourir tou les robots qui sont connectés
	dessin_liens()}
**/
