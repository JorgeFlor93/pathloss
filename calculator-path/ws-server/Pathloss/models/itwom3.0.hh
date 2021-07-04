#ifndef _ITWOM30_HH_
#define _ITWOM30_HH_

double point_to_point_ITM(double tht_m, double rht_m, double eps_dielect,
			double sgm_conductivity, double eno_ns_surfref,
			double frq_mhz, int radio_climate, int pol,
			double conf, double rel, double &dbloss, char *strmode,
			int &errnum);
double point_to_point(double tht_m, double rht_m, double eps_dielect,
		    double sgm_conductivity, double eno_ns_surfref,
		    double frq_mhz, int radio_climate, int pol, double conf,
		    double rel);

#endif /* _ITWOM30_HH_ */
