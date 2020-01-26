#ifndef _PEANO4_GRID_GRIDSTATISTICS_H
#define _PEANO4_GRID_GRIDSTATISTICS_H

#include "config.h"
#ifdef Parallel
	#include "tarch/mpi/Rank.h"
#endif
#include "tarch/logging/Log.h"
#include "tarch/la/Vector.h"
#include <bitset>
#include <complex>
#include <string>
#include <iostream>

namespace peano4 {
   namespace grid {
      class GridStatistics;
      class GridStatisticsPacked;
   }
}

/**
 * @author This class is generated by DaStGen
 * 		   DataStructureGenerator (DaStGen)
 * 		   2007-2009 Wolfgang Eckhardt
 * 		   2012      Tobias Weinzierl
 *
 * 		   build date: 09-02-2014 14:40
 *
 * @date   26/01/2020 20:18
 */
class peano4::grid::GridStatistics { 
   
   public:
      
      typedef peano4::grid::GridStatisticsPacked Packed;
      
      struct PersistentRecords {
         int _numberOfRefinedVertices;
         int _numberOfUnrefinedVertices;
         int _numberOfErasingVertices;
         int _numberOfRefiningVertices;
         int _numberOfLocalUnrefinedCells;
         int _numberOfRemoteUnrefinedCells;
         int _numberOfLocalRefinedCells;
         int _numberOfRemoteRefinedCells;
         int _stationarySweeps;
         bool _coarseningHasBeenVetoed;
         /**
          * Generated
          */
         PersistentRecords();
         
         /**
          * Generated
          */
         PersistentRecords(const int& numberOfRefinedVertices, const int& numberOfUnrefinedVertices, const int& numberOfErasingVertices, const int& numberOfRefiningVertices, const int& numberOfLocalUnrefinedCells, const int& numberOfRemoteUnrefinedCells, const int& numberOfLocalRefinedCells, const int& numberOfRemoteRefinedCells, const int& stationarySweeps, const bool& coarseningHasBeenVetoed);
         
         /**
          * Generated
          */
          int getNumberOfRefinedVertices() const ;
         
         /**
          * Generated
          */
          void setNumberOfRefinedVertices(const int& numberOfRefinedVertices) ;
         
         /**
          * Generated
          */
          int getNumberOfUnrefinedVertices() const ;
         
         /**
          * Generated
          */
          void setNumberOfUnrefinedVertices(const int& numberOfUnrefinedVertices) ;
         
         /**
          * Generated
          */
          int getNumberOfErasingVertices() const ;
         
         /**
          * Generated
          */
          void setNumberOfErasingVertices(const int& numberOfErasingVertices) ;
         
         /**
          * Generated
          */
          int getNumberOfRefiningVertices() const ;
         
         /**
          * Generated
          */
          void setNumberOfRefiningVertices(const int& numberOfRefiningVertices) ;
         
         /**
          * Generated
          */
          int getNumberOfLocalUnrefinedCells() const ;
         
         /**
          * Generated
          */
          void setNumberOfLocalUnrefinedCells(const int& numberOfLocalUnrefinedCells) ;
         
         /**
          * Generated
          */
          int getNumberOfRemoteUnrefinedCells() const ;
         
         /**
          * Generated
          */
          void setNumberOfRemoteUnrefinedCells(const int& numberOfRemoteUnrefinedCells) ;
         
         /**
          * Generated
          */
          int getNumberOfLocalRefinedCells() const ;
         
         /**
          * Generated
          */
          void setNumberOfLocalRefinedCells(const int& numberOfLocalRefinedCells) ;
         
         /**
          * Generated
          */
          int getNumberOfRemoteRefinedCells() const ;
         
         /**
          * Generated
          */
          void setNumberOfRemoteRefinedCells(const int& numberOfRemoteRefinedCells) ;
         
         /**
          * Generated
          */
          int getStationarySweeps() const ;
         
         /**
          * Generated
          */
          void setStationarySweeps(const int& stationarySweeps) ;
         
         /**
          * Generated
          */
          bool getCoarseningHasBeenVetoed() const ;
         
         /**
          * Generated
          */
          void setCoarseningHasBeenVetoed(const bool& coarseningHasBeenVetoed) ;
         
         
      };
      private: 
         PersistentRecords _persistentRecords;
         
      public:
         /**
          * Generated
          */
         GridStatistics();
         
         /**
          * Generated
          */
         GridStatistics(const PersistentRecords& persistentRecords);
         
         /**
          * Generated
          */
         GridStatistics(const int& numberOfRefinedVertices, const int& numberOfUnrefinedVertices, const int& numberOfErasingVertices, const int& numberOfRefiningVertices, const int& numberOfLocalUnrefinedCells, const int& numberOfRemoteUnrefinedCells, const int& numberOfLocalRefinedCells, const int& numberOfRemoteRefinedCells, const int& stationarySweeps, const bool& coarseningHasBeenVetoed);
         
         /**
          * Generated
          */
         virtual ~GridStatistics();
         
         /**
          * Generated
          */
          int getNumberOfRefinedVertices() const ;
         
         /**
          * Generated
          */
          void setNumberOfRefinedVertices(const int& numberOfRefinedVertices) ;
         
         /**
          * Generated
          */
          int getNumberOfUnrefinedVertices() const ;
         
         /**
          * Generated
          */
          void setNumberOfUnrefinedVertices(const int& numberOfUnrefinedVertices) ;
         
         /**
          * Generated
          */
          int getNumberOfErasingVertices() const ;
         
         /**
          * Generated
          */
          void setNumberOfErasingVertices(const int& numberOfErasingVertices) ;
         
         /**
          * Generated
          */
          int getNumberOfRefiningVertices() const ;
         
         /**
          * Generated
          */
          void setNumberOfRefiningVertices(const int& numberOfRefiningVertices) ;
         
         /**
          * Generated
          */
          int getNumberOfLocalUnrefinedCells() const ;
         
         /**
          * Generated
          */
          void setNumberOfLocalUnrefinedCells(const int& numberOfLocalUnrefinedCells) ;
         
         /**
          * Generated
          */
          int getNumberOfRemoteUnrefinedCells() const ;
         
         /**
          * Generated
          */
          void setNumberOfRemoteUnrefinedCells(const int& numberOfRemoteUnrefinedCells) ;
         
         /**
          * Generated
          */
          int getNumberOfLocalRefinedCells() const ;
         
         /**
          * Generated
          */
          void setNumberOfLocalRefinedCells(const int& numberOfLocalRefinedCells) ;
         
         /**
          * Generated
          */
          int getNumberOfRemoteRefinedCells() const ;
         
         /**
          * Generated
          */
          void setNumberOfRemoteRefinedCells(const int& numberOfRemoteRefinedCells) ;
         
         /**
          * Generated
          */
          int getStationarySweeps() const ;
         
         /**
          * Generated
          */
          void setStationarySweeps(const int& stationarySweeps) ;
         
         /**
          * Generated
          */
          bool getCoarseningHasBeenVetoed() const ;
         
         /**
          * Generated
          */
          void setCoarseningHasBeenVetoed(const bool& coarseningHasBeenVetoed) ;
         
         /**
          * Generated
          */
         std::string toString() const;
         
         /**
          * Generated
          */
         void toString(std::ostream& out) const;
         
         
         PersistentRecords getPersistentRecords() const;
         /**
          * Generated
          */
         GridStatisticsPacked convert() const;
         
         
      #ifdef Parallel
         protected:
            static tarch::logging::Log _log;
            
            int _senderDestinationRank;
            
         public:
            
            /**
             * Global that represents the mpi datatype.
             * There are two variants: Datatype identifies only those attributes marked with
             * parallelise. FullDatatype instead identifies the whole record with all fields.
             */
            static MPI_Datatype Datatype;
            static MPI_Datatype FullDatatype;
            
            /**
             * Initializes the data type for the mpi operations. Has to be called
             * before the very first send or receive operation is called.
             */
            static void initDatatype();
            
            static void shutdownDatatype();
            
            enum class ExchangeMode { Blocking, NonblockingWithPollingLoopOverTests, LoopOverProbeWithBlockingReceive };
            
            void send(int destination, int tag, bool exchangeOnlyAttributesMarkedWithParallelise, ExchangeMode mode );
            
            void receive(int source, int tag, bool exchangeOnlyAttributesMarkedWithParallelise, ExchangeMode mode );
            
            static bool isMessageInQueue(int tag, bool exchangeOnlyAttributesMarkedWithParallelise);
            
            int getSenderRank() const;
            #endif
   
};

/**
 * @author This class is generated by DaStGen
 * 		   DataStructureGenerator (DaStGen)
 * 		   2007-2009 Wolfgang Eckhardt
 * 		   2012      Tobias Weinzierl
 *
 * 		   build date: 09-02-2014 14:40
 *
 * @date   26/01/2020 20:18
 */
class peano4::grid::GridStatisticsPacked { 
   
   public:
      
      struct PersistentRecords {
         int _numberOfRefinedVertices;
         int _numberOfUnrefinedVertices;
         int _numberOfErasingVertices;
         int _numberOfRefiningVertices;
         int _numberOfLocalUnrefinedCells;
         int _numberOfRemoteUnrefinedCells;
         int _numberOfLocalRefinedCells;
         int _numberOfRemoteRefinedCells;
         int _stationarySweeps;
         
         /** mapping of records:
         || Member 	|| startbit 	|| length
          |  coarseningHasBeenVetoed	| startbit 0	| #bits 1
          */
         short int _packedRecords0;
         
         /**
          * Generated
          */
         PersistentRecords();
         
         /**
          * Generated
          */
         PersistentRecords(const int& numberOfRefinedVertices, const int& numberOfUnrefinedVertices, const int& numberOfErasingVertices, const int& numberOfRefiningVertices, const int& numberOfLocalUnrefinedCells, const int& numberOfRemoteUnrefinedCells, const int& numberOfLocalRefinedCells, const int& numberOfRemoteRefinedCells, const int& stationarySweeps, const bool& coarseningHasBeenVetoed);
         
         /**
          * Generated
          */
          int getNumberOfRefinedVertices() const ;
         
         /**
          * Generated
          */
          void setNumberOfRefinedVertices(const int& numberOfRefinedVertices) ;
         
         /**
          * Generated
          */
          int getNumberOfUnrefinedVertices() const ;
         
         /**
          * Generated
          */
          void setNumberOfUnrefinedVertices(const int& numberOfUnrefinedVertices) ;
         
         /**
          * Generated
          */
          int getNumberOfErasingVertices() const ;
         
         /**
          * Generated
          */
          void setNumberOfErasingVertices(const int& numberOfErasingVertices) ;
         
         /**
          * Generated
          */
          int getNumberOfRefiningVertices() const ;
         
         /**
          * Generated
          */
          void setNumberOfRefiningVertices(const int& numberOfRefiningVertices) ;
         
         /**
          * Generated
          */
          int getNumberOfLocalUnrefinedCells() const ;
         
         /**
          * Generated
          */
          void setNumberOfLocalUnrefinedCells(const int& numberOfLocalUnrefinedCells) ;
         
         /**
          * Generated
          */
          int getNumberOfRemoteUnrefinedCells() const ;
         
         /**
          * Generated
          */
          void setNumberOfRemoteUnrefinedCells(const int& numberOfRemoteUnrefinedCells) ;
         
         /**
          * Generated
          */
          int getNumberOfLocalRefinedCells() const ;
         
         /**
          * Generated
          */
          void setNumberOfLocalRefinedCells(const int& numberOfLocalRefinedCells) ;
         
         /**
          * Generated
          */
          int getNumberOfRemoteRefinedCells() const ;
         
         /**
          * Generated
          */
          void setNumberOfRemoteRefinedCells(const int& numberOfRemoteRefinedCells) ;
         
         /**
          * Generated
          */
          int getStationarySweeps() const ;
         
         /**
          * Generated
          */
          void setStationarySweeps(const int& stationarySweeps) ;
         
         /**
          * Generated
          */
          bool getCoarseningHasBeenVetoed() const ;
         
         /**
          * Generated
          */
          void setCoarseningHasBeenVetoed(const bool& coarseningHasBeenVetoed) ;
         
         
      };
      private: 
         PersistentRecords _persistentRecords;
         
      public:
         /**
          * Generated
          */
         GridStatisticsPacked();
         
         /**
          * Generated
          */
         GridStatisticsPacked(const PersistentRecords& persistentRecords);
         
         /**
          * Generated
          */
         GridStatisticsPacked(const int& numberOfRefinedVertices, const int& numberOfUnrefinedVertices, const int& numberOfErasingVertices, const int& numberOfRefiningVertices, const int& numberOfLocalUnrefinedCells, const int& numberOfRemoteUnrefinedCells, const int& numberOfLocalRefinedCells, const int& numberOfRemoteRefinedCells, const int& stationarySweeps, const bool& coarseningHasBeenVetoed);
         
         /**
          * Generated
          */
         virtual ~GridStatisticsPacked();
         
         /**
          * Generated
          */
          int getNumberOfRefinedVertices() const ;
         
         /**
          * Generated
          */
          void setNumberOfRefinedVertices(const int& numberOfRefinedVertices) ;
         
         /**
          * Generated
          */
          int getNumberOfUnrefinedVertices() const ;
         
         /**
          * Generated
          */
          void setNumberOfUnrefinedVertices(const int& numberOfUnrefinedVertices) ;
         
         /**
          * Generated
          */
          int getNumberOfErasingVertices() const ;
         
         /**
          * Generated
          */
          void setNumberOfErasingVertices(const int& numberOfErasingVertices) ;
         
         /**
          * Generated
          */
          int getNumberOfRefiningVertices() const ;
         
         /**
          * Generated
          */
          void setNumberOfRefiningVertices(const int& numberOfRefiningVertices) ;
         
         /**
          * Generated
          */
          int getNumberOfLocalUnrefinedCells() const ;
         
         /**
          * Generated
          */
          void setNumberOfLocalUnrefinedCells(const int& numberOfLocalUnrefinedCells) ;
         
         /**
          * Generated
          */
          int getNumberOfRemoteUnrefinedCells() const ;
         
         /**
          * Generated
          */
          void setNumberOfRemoteUnrefinedCells(const int& numberOfRemoteUnrefinedCells) ;
         
         /**
          * Generated
          */
          int getNumberOfLocalRefinedCells() const ;
         
         /**
          * Generated
          */
          void setNumberOfLocalRefinedCells(const int& numberOfLocalRefinedCells) ;
         
         /**
          * Generated
          */
          int getNumberOfRemoteRefinedCells() const ;
         
         /**
          * Generated
          */
          void setNumberOfRemoteRefinedCells(const int& numberOfRemoteRefinedCells) ;
         
         /**
          * Generated
          */
          int getStationarySweeps() const ;
         
         /**
          * Generated
          */
          void setStationarySweeps(const int& stationarySweeps) ;
         
         /**
          * Generated
          */
          bool getCoarseningHasBeenVetoed() const ;
         
         /**
          * Generated
          */
          void setCoarseningHasBeenVetoed(const bool& coarseningHasBeenVetoed) ;
         
         /**
          * Generated
          */
         std::string toString() const;
         
         /**
          * Generated
          */
         void toString(std::ostream& out) const;
         
         
         PersistentRecords getPersistentRecords() const;
         /**
          * Generated
          */
         GridStatistics convert() const;
         
         
      #ifdef Parallel
         protected:
            static tarch::logging::Log _log;
            
            int _senderDestinationRank;
            
         public:
            
            /**
             * Global that represents the mpi datatype.
             * There are two variants: Datatype identifies only those attributes marked with
             * parallelise. FullDatatype instead identifies the whole record with all fields.
             */
            static MPI_Datatype Datatype;
            static MPI_Datatype FullDatatype;
            
            /**
             * Initializes the data type for the mpi operations. Has to be called
             * before the very first send or receive operation is called.
             */
            static void initDatatype();
            
            static void shutdownDatatype();
            
            enum class ExchangeMode { Blocking, NonblockingWithPollingLoopOverTests, LoopOverProbeWithBlockingReceive };
            
            void send(int destination, int tag, bool exchangeOnlyAttributesMarkedWithParallelise, ExchangeMode mode );
            
            void receive(int source, int tag, bool exchangeOnlyAttributesMarkedWithParallelise, ExchangeMode mode );
            
            static bool isMessageInQueue(int tag, bool exchangeOnlyAttributesMarkedWithParallelise);
            
            int getSenderRank() const;
            #endif
   
};

#endif

