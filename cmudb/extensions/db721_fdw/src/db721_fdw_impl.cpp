// If you choose to use C++, read this very carefully:
// https://www.postgresql.org/docs/15/xfunc-c.html#EXTEND-CPP
// /workspaces/cmu-db/contrib/postgres_fdw/postgres_fdw.h
// src/include/nodes/pathnodes.h
// src/include/parser/parsetree.h
//src/include/commands/defrem.h
#include "dog.h"

// clang-format off
extern "C" {
#include "../../../../src/include/postgres.h"
#include "../../../../src/include/fmgr.h"
#include "../../../../src/include/foreign/fdwapi.h"
#include "../../../../src/include/parser/parsetree.h"
#include "../../../../src/include/optimizer/pathnode.h"
#include "../../../../src/include/nodes/pathnodes.h"
#include "../../../../src/include/commands/defrem.h"
#include "../../../contrib/postgres_fdw/postgres_fdw.h"
}
// clang-format on

extern "C" void db721_GetForeignRelSize(PlannerInfo *root, RelOptInfo *baserel,
                                      Oid foreigntableid) {
  // TODO(721): Write me!
  Dog terrier("Terrier");
  baserel->rows=100;
PgFdwRelationInfo *fpinfo;
	ListCell   *lc;
	RangeTblEntry *rte = planner_rt_fetch(baserel->relid, root);

	/*
	 * We use PgFdwRelationInfo to pass various information to subsequent
	 * functions.
	 */
	fpinfo = (PgFdwRelationInfo *) palloc0(sizeof(PgFdwRelationInfo));
	baserel->fdw_private = (void *) fpinfo;

	/* Base foreign tables need to be pushed down always. */
	fpinfo->pushdown_safe = true;

	/* Look up foreign-table catalog info. */
	fpinfo->table = GetForeignTable(foreigntableid);
	fpinfo->server = GetForeignServer(fpinfo->table->serverid);

	/*
	 * Extract user-settable option values.  Note that per-table settings of
	 * use_remote_estimate, fetch_size and async_capable override per-server
	 * settings of them, respectively.
	 */
	fpinfo->use_remote_estimate = false;
	fpinfo->fdw_startup_cost = 100.0;
	fpinfo->fdw_tuple_cost = 0.1;
	fpinfo->shippable_extensions = NIL;
	fpinfo->fetch_size = 100;
	fpinfo->async_capable = false;

  fpinfo->startup_cost=100;
  fpinfo->total_cost=300;

  auto options = fpinfo -> table->options;
  auto op1 = list_head(options);
  auto op2 = list_second_cell(options);
  
  DefElem    *def = (DefElem *) lfirst(op1);
  auto x1 = def->defname;
  auto *filename = defGetString(def);
  def = (DefElem *) lfirst(op2);
  x1 = def -> defname;
  auto *tableName=defGetString(def);
  elog(WARNING,"filename is %s and tablename is %s ",filename,tableName);
		// if (strcmp(def->defname, "filename") == 0)
		// {
		// 	*filename = defGetString(def);
		// 	options = foreach_delete_current(options, lc);
		// 	break;
		// }

  // baserel->cheapest_startup_path
  elog(WARNING,"Happy 1");
  elog(LOG, "db721_GetForeignRelSize: %s", terrier.Bark().c_str());
}

/*
 * create_foreignscan_path
 *	  Creates a path corresponding to a scan of a foreign base table,
 *	  returning the pathnode.
 *
 * This function is never called from core Postgres; rather, it's expected
 * to be called by the GetForeignPaths function of a foreign data wrapper.
 * We make the FDW supply all fields of the path, since we do not have any way
 * to calculate them in core.  However, there is a usually-sane default for
 * the pathtarget (rel->reltarget), so we let a NULL for "target" select that.
//  */
// ForeignPath *
// create_foreignscan_path(PlannerInfo *root, RelOptInfo *rel,
// 						PathTarget *target,
// 						double rows, Cost startup_cost, Cost total_cost,
// 						List *pathkeys,
// 						Relids required_outer,
// 						Path *fdw_outerpath,
// 						List *fdw_private)

// /workspaces/cmu-db/build/postgres/lib/db721_fdw.so
// /workspaces/cmu-db/cmudb/extensions/db721_fdw/src/db721_fdw.o
extern "C" void db721_GetForeignPaths(PlannerInfo *root, RelOptInfo *baserel,
                                    Oid foreigntableid) {
  // TODO(721): Write me!
  Dog scout("Scout");
  elog(WARNING,"Happy 2");
  // PathTarget target;
  //  auto x1 = create_foreignscan_path(root,baserel,baserel->reltarget,100,200,300,NULL,baserel->all_partrels,NULL,NULL);

  // //  auto x1 = create_foreignscan_path()
  // baserel->pathlist
 PgFdwRelationInfo *fpinfo = (PgFdwRelationInfo *) baserel->fdw_private;
	ForeignPath *path;
	// List	   *ppi_list;
	// ListCell   *lc;

	/*
	 * Create simplest ForeignScan path node and add it to baserel.  This path
	 * corresponds to SeqScan path of regular tables (though depending on what
	 * baserestrict conditions we were able to send to remote, there might
	 * actually be an indexscan happening there).  We already did all the work
	 * to estimate cost and size of this path.
	 *
	 * Although this path uses no join clauses, it could still have required
	 * parameterization due to LATERAL refs in its tlist.
	 */
	path = create_foreignscan_path(root, baserel,
								   NULL,	/* default pathtarget */
								   fpinfo->rows,
								   fpinfo->startup_cost,
								   fpinfo->total_cost,
								   NIL, /* no pathkeys */
								   baserel->lateral_relids,
								   NULL,	/* no extra plan */
								   NIL);	/* no fdw_private list */
	add_path(baserel, (Path *) path);

	/* Add paths with pathkeys */
	// add_paths_with_pathkeys_for_rel(root, baserel, NULL);


  elog(LOG, "db721_GetForeignPaths: %s", scout.Bark().c_str());
}

extern "C" ForeignScan *
db721_GetForeignPlan(PlannerInfo *root, RelOptInfo *baserel, Oid foreigntableid,
                   ForeignPath *best_path, List *tlist, List *scan_clauses,
                   Plan *outer_plan) {
  // TODO(721): Write me!
  elog(WARNING,"Happy 3");
  return nullptr;
}

extern "C" void db721_BeginForeignScan(ForeignScanState *node, int eflags) {
  // TODO(721): Write me!
  elog(WARNING,"Happy 4");
}

extern "C" TupleTableSlot *db721_IterateForeignScan(ForeignScanState *node) {
  // TODO(721): Write me!
  elog(WARNING,"Happy 5");
  return nullptr;
}

extern "C" void db721_ReScanForeignScan(ForeignScanState *node) {
  // TODO(721): Write me!
  elog(WARNING,"Happy 6");
}

extern "C" void db721_EndForeignScan(ForeignScanState *node) {
  // TODO(721): Write me!
  elog(WARNING,"Happy 7");
}