#MakeFile'in c++ dosyalarini derlemesi icin 2 tane alt klasor gerekli. Birincisi, 'source' alt klasoru. Bu klasor butun .cpp ve .h dosyaarini #icermeli. Ikincisi, 'build' alt klasoru. Bu ilk basta bos bir klasor, Makefile'i terminalden 'make' ile calistirdigimizda kendiliginden .o #dosyalariyla dolacaktir. Kisaca, Makefile'in oldugu path'de 2 alt klasor var. Yoksa calismaz. 

target = heritage
objects = Point.o Rectangle.o Cercle.o Ligne.o PolyLigne.o ObjetAgrege.o main.o LectureEcriture.o Figure.o ElementGeo.o 
CXX = g++
CPPFLAGS = -I include
.PHONY: all clean


# Shouldn't need to change anything below here...



OBJDIR = build
VPATH = $(OBJDIR)
OBJPROG = $(addprefix $(OBJDIR)/, $(target))

all: $(OBJPROG)
$(OBJPROG): $(addprefix $(OBJDIR)/, $(objects)) ; $(CXX) $(CPPFLAGS) $^ -o $@ 

$(OBJDIR)/%.o : source/%.cpp ; $(CXX) $(CPPFLAGS) -c $< -o $@

               
                        


