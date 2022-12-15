## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = projet2

projet2_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	BureauVote.c BureauVote.h \
	gesrec.c gesrec.h \
<<<<<<< HEAD
	crudCandidat.c crudCandidat.h
=======
	ges_elec.c ges_elec.h
>>>>>>> 680a2a4b1b96777c30aad29dba270fbc626c19b0

projet2_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

