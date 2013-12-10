
#---------------------------------
# INITIALISATION DES VARIABLES
#---------------------------------

# Indiquer le compilateur
CXX= gcc

# Les chemins ou se trouvent les fichiers a inclure
INCLUDE= -I/usr/include

# Options de compilation.
CXXFLAGS=  $(INCLUDE) -c -Wno-deprecated

# Les chemins ou se trouvent les librairies
LIBRARY_PATH= -L/usr/lib

# Options pour le linker.
LDFLAGS= $(LIBRARY_PATH) -o

# Les librairies avec lesquelle on va effectueller l'edition de liens
LIBS= -lpthread

# Les fichiers sources de l'application
FILES= main.c cercle.c robot.c produit.c

#-----------
# LES CIBLES
#-----------
main :  $(FILES:.c=.o)
	$(CXX) $(LDFLAGS) main $(FILES:.c=.o) $(LIBS)

.PHONY : clean
clean:
	/bin/rm $(FILES:.c=.o) main

#-----------------------------------------------------------------------------
# LES REGLES DE DEPENDANCE. Certaines sont implicites mais je recommande d'en
# mettre une par fichier source.
#-----------------------------------------------------------------------------
cercle.o:cercle.c
robot.o:robot.c
produit.o: produit.c
main.o:main.c cercle.h robot.h produit.h
#---------------------------------
# REGLES DE COMPILATION IMPLICITES
#---------------------------------
%.o : %.c ; $(CXX) $(CXXFLAGS) $*.c
