#include <gtkmm.h>

#include <gtkmm/window.h>
#include "graphic.h"

#define GTK_COMPATIBILITY_MODE

#ifdef GTK_COMPATIBILITY_MODE

class Scroll : public Gtk::Frame
{

public:
  Scroll();
  virtual ~Scroll();
  void tree_view_update(); // necessary for the project

private:
  //layout
  Gtk::Box _v_box;

  //Signal handlers:
  void on_button_clicked();

  //Member widgets:
  Gtk::Button m_button;
  
  // necessary for the project: internal class for private use of scrolledWindow
  class Model_columns : public Gtk::TreeModel::ColumnRecord
  {
   public:
     Model_columns()
     {
       add(_col_id);
       add(_col_nbP);
       add(_col_nbF);
       add(_col_nbT);
       add(_col_nbC);
       add(_col_resource);
       add(_col_resource_percentage);
     }

     Gtk::TreeModelColumn<int> _col_id;
     Gtk::TreeModelColumn<int> _col_nbP;
     Gtk::TreeModelColumn<int> _col_nbF;
     Gtk::TreeModelColumn<int> _col_nbT;
     Gtk::TreeModelColumn<int> _col_nbC;
     Gtk::TreeModelColumn<double> 	_col_resource;
     Gtk::TreeModelColumn<int> _col_resource_percentage;
  };

  Model_columns _columns;

  Gtk::ScrolledWindow _scrolled_window;
  Gtk::TreeView _tree_view;

  unsigned count;
};


class Windowx : public Gtk::Window
{
public:
  Windowx();
  virtual ~Windowx();

protected:
  //Signal handlers:
  void on_button_clicked();

  //Child widgets:
  Scroll scroll;
  MyArea Area;
  Gtk::Box m_box, m_box_Bottom, m_box_Top, m_box_Button, m_box_General, m_box_Display,
		m_box_Draw;
  Gtk::Frame m_Frame_Horizontal, m_Frame_Vertical;
  Gtk::Label m_Label_LineWrapped;
};

//Classe pour tous les boutons generaux
class ButtonBox : public Gtk::Frame
{
public:
  ButtonBox(bool horizontal, const Glib::ustring& title, gint spacing, 
			Gtk::ButtonBoxStyle layout);

protected:
	Gtk::Button m_Button_Exit,m_Button_Start,m_Button_Open, m_Button_Step, 
				m_Button_Save;
};


//Classe pour les boutons de Toogle Display
class ButtonBox2 : public Gtk::Frame
{
public:
  ButtonBox2(	bool horizontal, const Glib::ustring& title, gint spacing,
				Gtk::ButtonBoxStyle layout);

protected:
	Gtk::Button m_Button_Link,m_Button_Range;
};




#endif //GTKMM_EXAMPLEWINDOW_H
