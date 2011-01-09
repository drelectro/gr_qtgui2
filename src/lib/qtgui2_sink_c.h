/* -*- c++ -*- */
/*
 * Copyright 2008,2009 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_QTGUI2_SINK_C_H
#define INCLUDED_QTGUI2_SINK_C_H

#include <Python.h>
#include <gr_block.h>
#include <gr_firdes.h>
#include <gri_fft.h>
#include <qapplication.h>
#include <qtgui2.h>
#include "SpectrumGUIClass.h"

class qtgui2_sink_c;
typedef boost::shared_ptr<qtgui2_sink_c> qtgui2_sink_c_sptr;

qtgui2_sink_c_sptr qtgui2_make_sink_c (int fftsize, int wintype,
				     double fc=0, double bandwidth=1.0,
				     const std::string &name="Spectrum Display",
				     bool plotfreq=true, bool plotwaterfall=true,
				     bool plotwaterfall3d=true, bool plottime=true,
				     bool plotconst=true,
                                     bool use_openGL=true,
                                     bool showform=true,
				     QWidget *parent=NULL);

class qtgui2_sink_c : public gr_block
{
private:
  friend qtgui2_sink_c_sptr qtgui2_make_sink_c (int fftsize, int wintype,
					      double fc, double bw,
					      const std::string &name,
					      bool plotfreq, bool plotwaterfall,
					      bool plotwaterfall3d, bool plottime,
					      bool plotconst,
                                              bool use_openGL,
                                              bool showform,
					      QWidget *parent);
  qtgui2_sink_c (int fftsize, int wintype,
		double fc, double bw, 
		const std::string &name,
		bool plotfreq, bool plotwaterfall,
		bool plotwaterfall3d, bool plottime,
		bool plotconst,
                bool use_openGL,
                bool showform,
		QWidget *parent);

  void forecast(int noutput_items, gr_vector_int &ninput_items_required);

  // use opengl to force OpenGL on or off
  // this might be necessary for sessions over SSH
  void initialize(const bool opengl=true);

  int d_fftsize;
  gr_firdes::win_type d_wintype;
  std::vector<float> d_window;
  double d_center_freq;
  double d_bandwidth;
  std::string d_name;
  
  pthread_mutex_t d_pmutex;

  bool d_shift;
  gri_fft_complex *d_fft;

  int d_index;
  gr_complex *d_residbuf;

  bool d_plotfreq, d_plotwaterfall, d_plottime, d_plotconst;
  
  double d_update_time;

  QWidget *d_parent;
  SpectrumGUIClass *d_main_gui;

  void windowreset();
  void buildwindow();
  void fftresize();
  void fft(const gr_complex *data_in, int size);
  
public:
  ~qtgui2_sink_c();
  void exec_();
  void lock();
  void unlock();
  QWidget*  qwidget();
  PyObject* pyqwidget();

  void set_frequency_range(const double centerfreq,
			   const double bandwidth);

  void set_time_domain_axis(double min, double max);
  void set_constellation_axis(double xmin, double xmax,
			      double ymin, double ymax);
  void set_constellation_pen_size(int size);
  void set_frequency_axis(double min, double max);

  void set_update_time(double t);

  QApplication *d_qApplication;
  qtgui2_obj *d_object;

  int general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);

  //MJC
  void set_trace_colour(const unsigned char r, const unsigned char g, const unsigned char b);
  void set_bg_colour(const unsigned char r, const unsigned char g, const unsigned char b);
  void set_use_rf_frequencies(bool userff);
  void set_show_cf_marker(bool show);
};

#endif /* INCLUDED_QTGUI2_SINK_C_H */
