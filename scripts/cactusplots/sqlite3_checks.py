#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import print_function
import sqlite3
import optparse

usage = "usage: %prog [options] sqlitedb"

parser = optparse.OptionParser(usage=usage)

# parser.add_option("--extraopts", "-e", metavar="OPTS",
                  #dest="extra_options", default="",
                  #help="Extra options to give to SAT solver")

# parser.add_option("--verbose", "-v", action="store_true", default=False,
                  #dest="verbose", help="Print more output")

(options, args) = parser.parse_args()

if len(args) != 1:
    print("ERROR: You must give exactly one argument, the sqlite3 database file")
    exit(-1)

dbfname = args[0]
print("Using sqlite3db file %s" % dbfname)

conn = sqlite3.connect(dbfname)
c = conn.cursor()

query = """
select name,elapsed,tag from timepassed,tags
where name != 'search' and elapsed > 20 and
tags.tagname="filename" and tags.runID = timepassed.runID
order by elapsed desc;
"""

for row in c.execute(query):
    operation = row[0]
    t = row[1]
    name = row[2].split("/")
    name = name[len(name)-1]
    if len(name) > 30:
        name = name[:30]
    print("file: %-32s op: %-20s Time: %.1f " % (name, operation, t))

conn.close()
exit(0)


#select timepassed.runID, tag,elapsed from timepassed,tags where name like 'shorten and str red%' and elapsed > 2 and tags.runID = timepassed.runID;

#select * from timepassed where elapsed > 20 and name not like 'search';

#select * from startup, solverRun, finishup where finishup.runID = solverRun.runID and (finishup.endTime - startup.startTime) < 30 and solverRun.version = "618b5e79fdd8a15918e19fb76ca08aa069f14b54" and solverRun.runID = startup.runID;

#select * from timepassed,solverRun where elapsed > 20 and name not like 'search' and name not like 'probe' and solverRun.runID = timepassed.runID and solverRun.version = "618b5e79fdd8a15918e19fb76ca08aa069f14b54";