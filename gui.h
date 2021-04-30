#define GTK_COMPATIBILITY_MODE

#ifdef GTK_COMPATIBILITY_MODE

#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>

class Window : public Gtk::Window
{
public:
  Window();
  virtual ~Window();

protected:
  //Signal handlers:
  void on_button_clicked();

  //Child widgets:
  Gtk::Box m_box, m_box_Bottom, m_box_Top, m_box_Button, m_box_General, m_box_Display,
		m_box_Draw;
  Gtk::Frame m_Frame_Horizontal, m_Frame_Vertical;
  Gtk::Label m_Label_LineWrapped;
};

//Classe pour tous les boutons generaux
class ButtonBox : public Gtk::Frame
{
public:
  ButtonBox(bool horizontal,
       const Glib::ustring& title,
       gint spacing,
       Gtk::ButtonBoxStyle layout);

protected:
	Gtk::Button m_Button_Exit,m_Button_Start,m_Button_Open, m_Button_Step, m_Button_Save;
};


//Classe pour les boutons de Toogle Display
class ButtonBox2 : public Gtk::Frame
{
public:
  ButtonBox2(bool horizontal,
       const Glib::ustring& title,
       gint spacing,
       Gtk::ButtonBoxStyle layout);

protected:
	Gtk::Button m_Button_Link,m_Button_Range;
};


#endif //GTKMM_EXAMPLEWINDOW_H
