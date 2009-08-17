/*
 *  sqlovdb.c
 *
 *  $Id$
 *
 *  SQL remote table layout and emote SQL generation
 *
 *  This file is part of the OpenLink Software Virtuoso Open-Source (VOS)
 *  project.
 *
 *  Copyright (C) 1998-2006 OpenLink Software
 *
 *  This project is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; only version 2 of the License, dated June 1991.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */

#include "libutil.h"
#include "odbcinc.h"
#include "sqlnode.h"
#include "sqlpar.h"
#include "sqlpfn.h"
#include "sqlcmps.h"
#include "remote.h"
#include "sqlrcomp.h"
#include "sqlbif.h"
#include "security.h"
#include "sqlintrp.h"
#include "sqlo.h"



void sqlg_dt_text (sqlo_t * so, df_elt_t * dt_dfe, remote_table_source_t * top_rts,
    char * text, size_t tlen, int * fill);


int
sqlo_depends_on_locus (df_elt_t * dfe, locus_t * loc)
{
  DO_SET (op_table_t *, dep, &dfe->dfe_tables)
    {
      if (dep->ot_is_group_dummy || dk_set_member (loc->loc_ots, (void*) dep))
	return 1;
    }
  END_DO_SET();
  return 0;
}

/*
   fake - the scalar subq_preds in an pass-trough dt should really be
   compiled as a end_node_t at the start (as it's done for the scalar
   subqueries & function calls.
 */


int
sqlo_is_local (sql_comp_t * sc, remote_ds_t * rds, ST * tree, int only_eq_comps)
{
  return ST_NOT_LOCAL;
}


int
sqlo_fits_in_locus (sqlo_t * so, locus_t * loc, df_elt_t * dfe)
{
  return 0;
}


locus_t *
sqlo_prev_locus (sqlo_t * so)
{
  return LOC_LOCAL;
}


int
sqlo_list_fits_in_locus (sqlo_t * so, locus_t * loc, dk_set_t dfe_list)
{
  return 0;
}




locus_t *
sqlo_new_locus (sqlo_t * so, remote_ds_t * rds)
{
  char name[10];
  TNEW (locus_t, loc);
  snprintf (name, sizeof (name), "L%d", so->so_locus_ctr++);
  loc->loc_name = t_box_string (name);
  loc->loc_rds = rds;
  return loc;
}

#define NO_VDB GPF_T1 ("This build does not include virtual database support.")

void
sqlo_table_new_locus (sqlo_t * so, df_elt_t * tb_dfe, remote_ds_t * rds, dk_set_t col_preds, dk_set_t * after_test, dk_set_t after_join_test, dk_set_t * vdb_join_test)
{
  NO_VDB;
}


void
sqlo_table_locus (sqlo_t * so, df_elt_t * tb_dfe, dk_set_t col_preds, dk_set_t * after_test, dk_set_t after_join_test, dk_set_t * vdb_join_test)
{
  tb_dfe->dfe_locus = LOC_LOCAL;
}


locus_t *
sqlo_dt_locus (sqlo_t * so, op_table_t * ot, locus_t * outer_loc)
{
  return LOC_LOCAL;
}


int
loc_supports_top_op (locus_t * loc, ST * tree)
{
  NO_VDB;
  return 0;
}


locus_t *
sqlo_is_single_locus (df_elt_t * dfe)
{
  return LOC_LOCAL;
}


int
sqlo_try_remote_hash (sqlo_t * so, df_elt_t * tb_dfe)
{
  return RHJ_LOCAL;
}


int
sqlo_remote_hash_filler (sqlo_t * so, df_elt_t * filler, df_elt_t * tb_dfe)
{
  NO_VDB;
  return 1;
}




locus_t *
sqlo_dfe_preferred_locus (sqlo_t * so, df_elt_t * super, df_elt_t * dfe)
{
  return LOC_LOCAL;
}


#define SQLO_VDB_SAVE
#define SQLO_VDB_RESTORE


void
sqlg_non_local (sqlo_t * so, df_elt_t * dfe)
{
  NO_VDB;
}






data_source_t *
sqlg_locus_rts (sqlo_t * so, df_elt_t * first_dfe, dk_set_t pre_code)
{
  NO_VDB;
  return NULL;
}


int
sqlo_is_contains_vdb_tb (sqlo_t *so, op_table_t *ot, char ctype, ST **args)
{
  return 0;
}
