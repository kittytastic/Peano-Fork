// This file is part of the Peano project. For conditions of distribution and
// use, please see the copyright notice at www.peano-framework.org
#ifndef _TOOLBOX_PARTICLE_TRAJECTORY_DATABASE_
#define _TOOLBOX_PARTICLE_TRAJECTORY_DATABASE_


#include "tarch/la/Vector.h"
#include "tarch/logging/Log.h"
#include "tarch/multicore/BooleanSemaphore.h"
#include "peano4/utils/Globals.h"

#include <string>
#include <map>
#include <list>


namespace toolbox {
  namespace particles {
    class TrajectoryDatabase;
  }
}


class toolbox::particles::TrajectoryDatabase {
  private:
    static tarch::logging::Log _log;

    std::string _fileName;
    double      _dataDelta;
    double      _positionDelta;
    int         _numberOfDataPointsPerParticle;

    const int   _deltaBetweenTwoDatabaseFlushes;
    int         _thresholdForNextDatabaseFlush;
    /**
     * @see TrajectoryDatabase()
     */
    const bool  _clearDatabaseAfterFlush;

    struct Entry {
      tarch::la::Vector<Dimensions,double>  x;
      double                                timestamp;
      double*                               data;

      Entry( const TrajectoryDatabase& database, const tarch::la::Vector<Dimensions,double>&  x_, double  timestamp_ );
    };

    std::map< std::pair<int,int>, std::list<Entry> >  _data;

    tarch::multicore::BooleanSemaphore        _semaphore;

    enum class AddSnapshotAction {
      Ignore,
      Append,
      Replace
    };

    /**
     * Can't be const as it locks the semaphore.
     */
    AddSnapshotAction getAction(
      const std::pair<int, int>&                  number,
      const tarch::la::Vector<Dimensions,double>& x,
      double                                      timestamp
    );

    AddSnapshotAction getAction(
      const std::pair<int, int>&                   number,
      const tarch::la::Vector<Dimensions,double>&  x,
      double                                       timestamp,
      int                                          numberOfDataEntries,
      double*                                      data
    );

    bool dumpDatabaseSnapshot() const;
  public:
    /**
     * Trajectory database
     *
     * The database dumps/stores data if and only if the delta of two particles is
     * bigger than a threshold. We always work with the max norm. There's two different
     * thresholds: one for the position, one for the data.
     *
     * @param clearDatabaseAfterFlush If this flag is set, each flush of the database
     *  will go into a separte file, and the code will clear the database after the
     *  flush. As a consequence, the database will never exceed the memory. However,
     *  you'll get a lot of files that you have to merge afterwards.
     */
    TrajectoryDatabase( int growthBetweenTwoDatabaseFlushes, double positionDelta = 1e-8, double dataDelta = 1e-8, bool clearDatabaseAfterFlush=true );
    ~TrajectoryDatabase();

    void clear();
    void dumpCSVFile();

    void setOutputFileName( const std::string& filename );
    void setDataDeltaBetweenTwoSnapshots( double value );
    void setPositionDeltaBetweenTwoSnapshots( double value );

    /**
     * A particle is always uniquely identified by two integers (an
     * integer pair). This way, we can initialise (hand out) particle
     * numbers without any semaphore.
     */
    void addParticleSnapshot(
      const std::pair<int, int>&                   number,
      double                                       timestamp,
      const tarch::la::Vector<Dimensions,double>&  x
    );

    void addParticleSnapshot(
      int                                          number0,
      int                                          number1,
      double                                       timestamp,
      const tarch::la::Vector<Dimensions,double>&  x
    );

    void addParticleSnapshot(
      const std::pair<int, int>&                   number,
      double                                       timestamp,
      const tarch::la::Vector<Dimensions,double>&  x,
      int                                          numberOfDataEntries,
      double*                                      data
    );

    void addParticleSnapshot(
      int                                          number0,
      int                                          number1,
      double                                       timestamp,
      const tarch::la::Vector<Dimensions,double>&  x,
      int                                          numberOfDataEntries,
      double*                                      data
    );
};


#endif
