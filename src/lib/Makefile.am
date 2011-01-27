#
# Copyright 2008,2009,2010 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

include $(top_srcdir)/Makefile.common

#/usr/include/qwt-qt4/qwt_plot.h

AM_CPPFLAGS = $(STD_DEFINES_AND_INCLUDES) $(PYTHON_CPPFLAGS) \
              $(QT_INCLUDES) -I. $(WITH_INCLUDES)

# Only include these files in the build if qtgui passes configure checks
# This is mostly to help make distcheck pass
QMAKE_SOURCES = 					\
	qtgui2_sink_c.moc.cc			\
	SpectrumGUIClass.moc.cc			\
	spectrumdisplaywidget.moc.cc		\
	FrequencyDisplayPlot.moc.cc	 	\
	TimeDomainDisplayPlot.moc.cc	\
	WaterfallDisplayPlot.moc.cc		\
	ConstellationDisplayPlot.moc.cc	\	
	spectrumdisplayform.ui.h

EXTRA_DIST = spectrumdisplayform.ui

BUILT_SOURCES = $(QMAKE_SOURCES)

# Build the normal library for C++ apps to link against
lib_LTLIBRARIES = libgnuradio-qtgui2.la

# These are the source files that go into the shared library
libgnuradio_qtgui2_la_SOURCES = 	\
	FrequencyDisplayPlot.cc 		\
	TimeDomainDisplayPlot.cc		\
	WaterfallDisplayPlot.cc			\
	waterfallGlobalData.cc			\
	ConstellationDisplayPlot.cc		\
	spectrumdisplaywidget.cc			\
	SpectrumGUIClass.cc				\
	spectrumUpdateEvents.cc			\
	plot_waterfall.cc				\
        qtgui_util.cc                           \
	qtgui2_sink_c.cc				\
	qtgui2_sink_f.cc

nodist_libgnuradio_qtgui2_la_SOURCES=$(BUILT_SOURCES)

# These headers get installed in ${prefix}/include/gnuradio
grinclude_HEADERS =				\
	FrequencyDisplayPlot.h		\
	TimeDomainDisplayPlot.h		\
	WaterfallDisplayPlot.h		\
	waterfallGlobalData.h		\
	ConstellationDisplayPlot.h	\
	highResTimeFunctions.h		\
	plot_waterfall.h			\
	spectrumdisplaywidget.h		\
	SpectrumGUIClass.h			\
	spectrumUpdateEvents.h		\
        qtgui_util.h                    \
	qtgui2.h					\
	qtgui2_sink_c.h				\
	qtgui2_sink_f.h

QT_MOC_FLAGS = -DQT_SHARED -DQT_NO_DEBUG -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB
%.moc.cc : %.h
	$(QT_MOC_EXEC) $(QT_MOC_FLAGS) -p $(srcdir) $< -o $@

%.ui.h : %.ui
	$(QT_UIC_EXEC) $< -o $@

# magic flags
libgnuradio_qtgui2_la_LDFLAGS = $(NO_UNDEFINED) $(LTVERSIONFLAGS)

libgnuradio_qtgui2_la_LIBADD = 		\
	$(GNURADIO_CORE_LA)	\
	-lstdc++		\
	$(QT_LIBS)

#if PYTHON
##############################
# SWIG interface and library

TOP_SWIG_IFILES = 		\
	qtgui2.i

# Install so that they end up available as:
#   import gnuradio.qtgui2
# This ends up at:
#   ${prefix}/lib/python${python_version}/site-packages/gnuradio
qtgui2_pythondir_category =	\
	gnuradio/qtgui2

# additional libraries for linking with the SWIG-generated library
qtgui2_la_swig_libadd =		\
	libgnuradio-qtgui2.la

include $(top_srcdir)/Makefile.swig

# add some of the variables generated inside the Makefile.swig.gen
BUILT_SOURCES += 		\
	$(swig_built_sources)
#endif

# Do not distribute built sources, they may contain generated paths
# which are invalid on other systems
no_dist_files = $(BUILT_SOURCES)
