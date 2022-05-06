lib_LTLIBRARIES = \
	kombyne.la

AM_CFLAGS = $(LTDLINCL) @pancake_cflags@ @kombynelite_cflags@
AM_CXXFLAGS = $(LTDLINCL) @pancake_cflags@ @kombynelite_cflags@
AM_LDFLAGS = -module -no-undefined -avoid-version

kombyne_la_SOURCES = \
	tinf_visualizer.cpp \
	Kombyne.h \
	Kombyne.cpp
kombyne_la_LIBADD = \
	@kombynelite_ldadd@
