# Definitions de macros

OUT = projet
CXX     = g++
CXXFLAGS = -Wall -std=c++11 
CXXFILES = projet.cc simulation.cc message.cc gisement.cc geomod.cc base.cc robot.cc gui.cc
LINKING = `pkg-config --cflags gtkmm-3.0`
LDLIBS = `pkg-config --libs gtkmm-3.0`
OFILES = projet.o simulation.o message.o gisement.o geomod.o base.o robot.o gui.o 

all: $(OUT)

# Definition de la premiere regle
	
$(OUT): $(OFILES)
	$(CXX) $(CXXFLAGS) $(LINKING) $(OFILES) -o $@ $(LDLIBS)
	
# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ prog

#
#-- Regles de dependances generees automatiquement

 #DO NOT DELETE THIS LINE

projet.o: projet.cc geomod.h simulation.h message.h gui.h
simulation.o: simulation.cc base.h geomod.h simulation.h robot.h \
 gisement.h constantes.h message.h
message.o: message.cc message.h
gisement.o: gisement.cc message.h gisement.h geomod.h
geomod.o: geomod.cc geomod.h constantes.h
base.o: base.cc base.h geomod.h simulation.h robot.h gisement.h message.h \
 constantes.h
robot.o: robot.cc robot.h gisement.h geomod.h
gui.o: gui.cc gui.h
