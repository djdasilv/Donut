# Definitions de macros

CXX     = g++
CXXFLAGS = -g -Wall -std=c++11
CXXFILES = projet.cc simulation.cc message.cc gisement.cc geomod.cc base.cc robot.cc
OFILES = projet.o simulation.o message.o	gisement.o geomod.o	base.o robot.o

# Definition de la premiere regle

projet: $(OFILES)
	$(CXX) $(OFILES) -o projet

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
projet.o: projet.cc geomod.h simulation.h message.h
simulation.o: simulation.cc simulation.h gisement.h geomod.h base.h
message.o: message.cc message.h
gisement.o: gisement.cc message.h gisement.h geomod.h
geomod.o: geomod.cc geomod.h
base.o: base.cc geomod.h base.h simulation.h gisement.h message.h
