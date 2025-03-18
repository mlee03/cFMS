#ifndef C_DATA_OVERRIDE_H
#define C_DATA_OVERRIDE_H

extern const int CFLOAT_MODE;
extern const int CDOUBLE_MODE;

extern void cFMS_data_override_init(int *atm_domain_id, int *ocn_domain_id, int *ice_domain_id, int *land_domain_id,
                                    int *land_domainUG_id, int *mode);

#endif
