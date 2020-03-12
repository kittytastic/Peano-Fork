#ifndef _PEANO4_GRID_GRIDVERTEX_H
#define _PEANO4_GRID_GRIDVERTEX_H

#include "config.h"
#include "peano4/utils/Globals.h"
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
      class GridVertex;
      class GridVertexPacked;
   }
}

#if !defined(PeanoDebug)
   /**
    * @author This class is generated by DaStGen
    * 		   DataStructureGenerator (DaStGen)
    * 		   2007-2009 Wolfgang Eckhardt
    * 		   2012      Tobias Weinzierl
    *
    * 		   build date: 09-02-2014 14:40
    *
    * @date   12/03/2020 20:04
    */
   class peano4::grid::GridVertex { 
      
      public:
         
         typedef peano4::grid::GridVertexPacked Packed;
         
         enum State {
            HangingVertex = 0, New = 1, Unrefined = 2, Refined = 3, RefinementTriggered = 4, Refining = 5, EraseTriggered = 6, Erasing = 7, Delete = 8
         };
         
         struct PersistentRecords {
            State _state;
            tarch::la::Vector<TwoPowerD,int> _adjacentRanks;
            bool _hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep;
            bool _isAntecessorOfRefinedVertexInCurrentTreeSweep;
            /**
             * Generated
             */
            PersistentRecords();
            
            /**
             * Generated
             */
            PersistentRecords(const State& state, const tarch::la::Vector<TwoPowerD,int>& adjacentRanks, const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep, const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep);
            
            /**
             * Generated
             */
             State getState() const ;
            
            /**
             * Generated
             */
             void setState(const State& state) ;
            
             tarch::la::Vector<TwoPowerD,int> getAdjacentRanks() const ;
            
             void setAdjacentRanks(const tarch::la::Vector<TwoPowerD,int>& adjacentRanks) ;
            
            /**
             * Generated
             */
             bool getHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep() const ;
            
            /**
             * Generated
             */
             void setHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep(const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep) ;
            
            /**
             * Generated
             */
             bool getIsAntecessorOfRefinedVertexInCurrentTreeSweep() const ;
            
            /**
             * Generated
             */
             void setIsAntecessorOfRefinedVertexInCurrentTreeSweep(const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep) ;
            
            
         };
         private: 
            PersistentRecords _persistentRecords;
            tarch::la::Vector<TwoPowerD,int> _backupOfAdjacentRanks;
            int _numberOfAdjacentRefinedLocalCells;
            
         public:
            /**
             * Generated
             */
            GridVertex();
            
            /**
             * Generated
             */
            GridVertex(const PersistentRecords& persistentRecords);
            
            /**
             * Generated
             */
            GridVertex(const State& state, const tarch::la::Vector<TwoPowerD,int>& adjacentRanks, const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep, const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep);
            
            /**
             * Generated
             */
            GridVertex(const State& state, const tarch::la::Vector<TwoPowerD,int>& adjacentRanks, const tarch::la::Vector<TwoPowerD,int>& backupOfAdjacentRanks, const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep, const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep, const int& numberOfAdjacentRefinedLocalCells);
            
            /**
             * Generated
             */
            virtual ~GridVertex();
            
            /**
             * Generated
             */
             State getState() const ;
            
            /**
             * Generated
             */
             void setState(const State& state) ;
            
             tarch::la::Vector<TwoPowerD,int> getAdjacentRanks() const ;
            
             void setAdjacentRanks(const tarch::la::Vector<TwoPowerD,int>& adjacentRanks) ;
            
             int getAdjacentRanks(int elementIndex) const ;
            
             void setAdjacentRanks(int elementIndex, const int& adjacentRanks) ;
            
             tarch::la::Vector<TwoPowerD,int> getBackupOfAdjacentRanks() const ;
            
             void setBackupOfAdjacentRanks(const tarch::la::Vector<TwoPowerD,int>& backupOfAdjacentRanks) ;
            
             int getBackupOfAdjacentRanks(int elementIndex) const ;
            
             void setBackupOfAdjacentRanks(int elementIndex, const int& backupOfAdjacentRanks) ;
            
            /**
             * Generated
             */
             bool getHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep() const ;
            
            /**
             * Generated
             */
             void setHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep(const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep) ;
            
            /**
             * Generated
             */
             bool getIsAntecessorOfRefinedVertexInCurrentTreeSweep() const ;
            
            /**
             * Generated
             */
             void setIsAntecessorOfRefinedVertexInCurrentTreeSweep(const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep) ;
            
            /**
             * Generated
             */
             int getNumberOfAdjacentRefinedLocalCells() const ;
            
            /**
             * Generated
             */
             void setNumberOfAdjacentRefinedLocalCells(const int& numberOfAdjacentRefinedLocalCells) ;
            
            /**
             * Generated
             */
            static std::string toString(const State& param);
            
            /**
             * Generated
             */
            static std::string getStateMapping();
            
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
            GridVertexPacked convert() const;
            
            
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
    * @date   12/03/2020 20:04
    */
   class peano4::grid::GridVertexPacked { 
      
      public:
         
         typedef peano4::grid::GridVertex::State State;
         
         struct PersistentRecords {
            tarch::la::Vector<TwoPowerD,int> _adjacentRanks;
            
            /** mapping of records:
            || Member 	|| startbit 	|| length
             |  state	| startbit 0	| #bits 4
             |  hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep	| startbit 4	| #bits 1
             |  isAntecessorOfRefinedVertexInCurrentTreeSweep	| startbit 5	| #bits 1
             */
            int _packedRecords0;
            
            /**
             * Generated
             */
            PersistentRecords();
            
            /**
             * Generated
             */
            PersistentRecords(const State& state, const tarch::la::Vector<TwoPowerD,int>& adjacentRanks, const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep, const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep);
            
            /**
             * Generated
             */
             State getState() const ;
            
            /**
             * Generated
             */
             void setState(const State& state) ;
            
             tarch::la::Vector<TwoPowerD,int> getAdjacentRanks() const ;
            
             void setAdjacentRanks(const tarch::la::Vector<TwoPowerD,int>& adjacentRanks) ;
            
            /**
             * Generated
             */
             bool getHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep() const ;
            
            /**
             * Generated
             */
             void setHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep(const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep) ;
            
            /**
             * Generated
             */
             bool getIsAntecessorOfRefinedVertexInCurrentTreeSweep() const ;
            
            /**
             * Generated
             */
             void setIsAntecessorOfRefinedVertexInCurrentTreeSweep(const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep) ;
            
            
         };
         private: 
            PersistentRecords _persistentRecords;
            tarch::la::Vector<TwoPowerD,int> _backupOfAdjacentRanks;
            int _numberOfAdjacentRefinedLocalCells;
            
         public:
            /**
             * Generated
             */
            GridVertexPacked();
            
            /**
             * Generated
             */
            GridVertexPacked(const PersistentRecords& persistentRecords);
            
            /**
             * Generated
             */
            GridVertexPacked(const State& state, const tarch::la::Vector<TwoPowerD,int>& adjacentRanks, const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep, const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep);
            
            /**
             * Generated
             */
            GridVertexPacked(const State& state, const tarch::la::Vector<TwoPowerD,int>& adjacentRanks, const tarch::la::Vector<TwoPowerD,int>& backupOfAdjacentRanks, const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep, const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep, const int& numberOfAdjacentRefinedLocalCells);
            
            /**
             * Generated
             */
            virtual ~GridVertexPacked();
            
            /**
             * Generated
             */
             State getState() const ;
            
            /**
             * Generated
             */
             void setState(const State& state) ;
            
             tarch::la::Vector<TwoPowerD,int> getAdjacentRanks() const ;
            
             void setAdjacentRanks(const tarch::la::Vector<TwoPowerD,int>& adjacentRanks) ;
            
             int getAdjacentRanks(int elementIndex) const ;
            
             void setAdjacentRanks(int elementIndex, const int& adjacentRanks) ;
            
             tarch::la::Vector<TwoPowerD,int> getBackupOfAdjacentRanks() const ;
            
             void setBackupOfAdjacentRanks(const tarch::la::Vector<TwoPowerD,int>& backupOfAdjacentRanks) ;
            
             int getBackupOfAdjacentRanks(int elementIndex) const ;
            
             void setBackupOfAdjacentRanks(int elementIndex, const int& backupOfAdjacentRanks) ;
            
            /**
             * Generated
             */
             bool getHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep() const ;
            
            /**
             * Generated
             */
             void setHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep(const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep) ;
            
            /**
             * Generated
             */
             bool getIsAntecessorOfRefinedVertexInCurrentTreeSweep() const ;
            
            /**
             * Generated
             */
             void setIsAntecessorOfRefinedVertexInCurrentTreeSweep(const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep) ;
            
            /**
             * Generated
             */
             int getNumberOfAdjacentRefinedLocalCells() const ;
            
            /**
             * Generated
             */
             void setNumberOfAdjacentRefinedLocalCells(const int& numberOfAdjacentRefinedLocalCells) ;
            
            /**
             * Generated
             */
            static std::string toString(const State& param);
            
            /**
             * Generated
             */
            static std::string getStateMapping();
            
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
            GridVertex convert() const;
            
            
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
   
   #elif defined(PeanoDebug)
      /**
       * @author This class is generated by DaStGen
       * 		   DataStructureGenerator (DaStGen)
       * 		   2007-2009 Wolfgang Eckhardt
       * 		   2012      Tobias Weinzierl
       *
       * 		   build date: 09-02-2014 14:40
       *
       * @date   12/03/2020 20:04
       */
      class peano4::grid::GridVertex { 
         
         public:
            
            typedef peano4::grid::GridVertexPacked Packed;
            
            enum State {
               HangingVertex = 0, New = 1, Unrefined = 2, Refined = 3, RefinementTriggered = 4, Refining = 5, EraseTriggered = 6, Erasing = 7, Delete = 8
            };
            
            struct PersistentRecords {
               State _state;
               tarch::la::Vector<TwoPowerD,int> _adjacentRanks;
               bool _hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep;
               bool _isAntecessorOfRefinedVertexInCurrentTreeSweep;
               tarch::la::Vector<Dimensions,double> _x;
               int _level;
               /**
                * Generated
                */
               PersistentRecords();
               
               /**
                * Generated
                */
               PersistentRecords(const State& state, const tarch::la::Vector<TwoPowerD,int>& adjacentRanks, const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep, const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep, const tarch::la::Vector<Dimensions,double>& x, const int& level);
               
               /**
                * Generated
                */
                State getState() const ;
               
               /**
                * Generated
                */
                void setState(const State& state) ;
               
                tarch::la::Vector<TwoPowerD,int> getAdjacentRanks() const ;
               
                void setAdjacentRanks(const tarch::la::Vector<TwoPowerD,int>& adjacentRanks) ;
               
               /**
                * Generated
                */
                bool getHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep() const ;
               
               /**
                * Generated
                */
                void setHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep(const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep) ;
               
               /**
                * Generated
                */
                bool getIsAntecessorOfRefinedVertexInCurrentTreeSweep() const ;
               
               /**
                * Generated
                */
                void setIsAntecessorOfRefinedVertexInCurrentTreeSweep(const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep) ;
               
                tarch::la::Vector<Dimensions,double> getX() const ;
               
                void setX(const tarch::la::Vector<Dimensions,double>& x) ;
               
               /**
                * Generated
                */
                int getLevel() const ;
               
               /**
                * Generated
                */
                void setLevel(const int& level) ;
               
               
            };
            private: 
               PersistentRecords _persistentRecords;
               tarch::la::Vector<TwoPowerD,int> _backupOfAdjacentRanks;
               int _numberOfAdjacentRefinedLocalCells;
               
            public:
               /**
                * Generated
                */
               GridVertex();
               
               /**
                * Generated
                */
               GridVertex(const PersistentRecords& persistentRecords);
               
               /**
                * Generated
                */
               GridVertex(const State& state, const tarch::la::Vector<TwoPowerD,int>& adjacentRanks, const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep, const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep, const tarch::la::Vector<Dimensions,double>& x, const int& level);
               
               /**
                * Generated
                */
               GridVertex(const State& state, const tarch::la::Vector<TwoPowerD,int>& adjacentRanks, const tarch::la::Vector<TwoPowerD,int>& backupOfAdjacentRanks, const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep, const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep, const int& numberOfAdjacentRefinedLocalCells, const tarch::la::Vector<Dimensions,double>& x, const int& level);
               
               /**
                * Generated
                */
               virtual ~GridVertex();
               
               /**
                * Generated
                */
                State getState() const ;
               
               /**
                * Generated
                */
                void setState(const State& state) ;
               
                tarch::la::Vector<TwoPowerD,int> getAdjacentRanks() const ;
               
                void setAdjacentRanks(const tarch::la::Vector<TwoPowerD,int>& adjacentRanks) ;
               
                int getAdjacentRanks(int elementIndex) const ;
               
                void setAdjacentRanks(int elementIndex, const int& adjacentRanks) ;
               
                tarch::la::Vector<TwoPowerD,int> getBackupOfAdjacentRanks() const ;
               
                void setBackupOfAdjacentRanks(const tarch::la::Vector<TwoPowerD,int>& backupOfAdjacentRanks) ;
               
                int getBackupOfAdjacentRanks(int elementIndex) const ;
               
                void setBackupOfAdjacentRanks(int elementIndex, const int& backupOfAdjacentRanks) ;
               
               /**
                * Generated
                */
                bool getHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep() const ;
               
               /**
                * Generated
                */
                void setHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep(const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep) ;
               
               /**
                * Generated
                */
                bool getIsAntecessorOfRefinedVertexInCurrentTreeSweep() const ;
               
               /**
                * Generated
                */
                void setIsAntecessorOfRefinedVertexInCurrentTreeSweep(const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep) ;
               
               /**
                * Generated
                */
                int getNumberOfAdjacentRefinedLocalCells() const ;
               
               /**
                * Generated
                */
                void setNumberOfAdjacentRefinedLocalCells(const int& numberOfAdjacentRefinedLocalCells) ;
               
                tarch::la::Vector<Dimensions,double> getX() const ;
               
                void setX(const tarch::la::Vector<Dimensions,double>& x) ;
               
                double getX(int elementIndex) const ;
               
                void setX(int elementIndex, const double& x) ;
               
               /**
                * Generated
                */
                int getLevel() const ;
               
               /**
                * Generated
                */
                void setLevel(const int& level) ;
               
               /**
                * Generated
                */
               static std::string toString(const State& param);
               
               /**
                * Generated
                */
               static std::string getStateMapping();
               
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
               GridVertexPacked convert() const;
               
               
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
       * @date   12/03/2020 20:04
       */
      class peano4::grid::GridVertexPacked { 
         
         public:
            
            typedef peano4::grid::GridVertex::State State;
            
            struct PersistentRecords {
               tarch::la::Vector<TwoPowerD,int> _adjacentRanks;
               tarch::la::Vector<Dimensions,double> _x;
               int _level;
               
               /** mapping of records:
               || Member 	|| startbit 	|| length
                |  state	| startbit 0	| #bits 4
                |  hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep	| startbit 4	| #bits 1
                |  isAntecessorOfRefinedVertexInCurrentTreeSweep	| startbit 5	| #bits 1
                */
               int _packedRecords0;
               
               /**
                * Generated
                */
               PersistentRecords();
               
               /**
                * Generated
                */
               PersistentRecords(const State& state, const tarch::la::Vector<TwoPowerD,int>& adjacentRanks, const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep, const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep, const tarch::la::Vector<Dimensions,double>& x, const int& level);
               
               /**
                * Generated
                */
                State getState() const ;
               
               /**
                * Generated
                */
                void setState(const State& state) ;
               
                tarch::la::Vector<TwoPowerD,int> getAdjacentRanks() const ;
               
                void setAdjacentRanks(const tarch::la::Vector<TwoPowerD,int>& adjacentRanks) ;
               
               /**
                * Generated
                */
                bool getHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep() const ;
               
               /**
                * Generated
                */
                void setHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep(const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep) ;
               
               /**
                * Generated
                */
                bool getIsAntecessorOfRefinedVertexInCurrentTreeSweep() const ;
               
               /**
                * Generated
                */
                void setIsAntecessorOfRefinedVertexInCurrentTreeSweep(const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep) ;
               
                tarch::la::Vector<Dimensions,double> getX() const ;
               
                void setX(const tarch::la::Vector<Dimensions,double>& x) ;
               
               /**
                * Generated
                */
                int getLevel() const ;
               
               /**
                * Generated
                */
                void setLevel(const int& level) ;
               
               
            };
            private: 
               PersistentRecords _persistentRecords;
               tarch::la::Vector<TwoPowerD,int> _backupOfAdjacentRanks;
               int _numberOfAdjacentRefinedLocalCells;
               
            public:
               /**
                * Generated
                */
               GridVertexPacked();
               
               /**
                * Generated
                */
               GridVertexPacked(const PersistentRecords& persistentRecords);
               
               /**
                * Generated
                */
               GridVertexPacked(const State& state, const tarch::la::Vector<TwoPowerD,int>& adjacentRanks, const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep, const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep, const tarch::la::Vector<Dimensions,double>& x, const int& level);
               
               /**
                * Generated
                */
               GridVertexPacked(const State& state, const tarch::la::Vector<TwoPowerD,int>& adjacentRanks, const tarch::la::Vector<TwoPowerD,int>& backupOfAdjacentRanks, const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep, const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep, const int& numberOfAdjacentRefinedLocalCells, const tarch::la::Vector<Dimensions,double>& x, const int& level);
               
               /**
                * Generated
                */
               virtual ~GridVertexPacked();
               
               /**
                * Generated
                */
                State getState() const ;
               
               /**
                * Generated
                */
                void setState(const State& state) ;
               
                tarch::la::Vector<TwoPowerD,int> getAdjacentRanks() const ;
               
                void setAdjacentRanks(const tarch::la::Vector<TwoPowerD,int>& adjacentRanks) ;
               
                int getAdjacentRanks(int elementIndex) const ;
               
                void setAdjacentRanks(int elementIndex, const int& adjacentRanks) ;
               
                tarch::la::Vector<TwoPowerD,int> getBackupOfAdjacentRanks() const ;
               
                void setBackupOfAdjacentRanks(const tarch::la::Vector<TwoPowerD,int>& backupOfAdjacentRanks) ;
               
                int getBackupOfAdjacentRanks(int elementIndex) const ;
               
                void setBackupOfAdjacentRanks(int elementIndex, const int& backupOfAdjacentRanks) ;
               
               /**
                * Generated
                */
                bool getHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep() const ;
               
               /**
                * Generated
                */
                void setHasBeenAntecessorOfRefinedVertexInPreviousTreeSweep(const bool& hasBeenAntecessorOfRefinedVertexInPreviousTreeSweep) ;
               
               /**
                * Generated
                */
                bool getIsAntecessorOfRefinedVertexInCurrentTreeSweep() const ;
               
               /**
                * Generated
                */
                void setIsAntecessorOfRefinedVertexInCurrentTreeSweep(const bool& isAntecessorOfRefinedVertexInCurrentTreeSweep) ;
               
               /**
                * Generated
                */
                int getNumberOfAdjacentRefinedLocalCells() const ;
               
               /**
                * Generated
                */
                void setNumberOfAdjacentRefinedLocalCells(const int& numberOfAdjacentRefinedLocalCells) ;
               
                tarch::la::Vector<Dimensions,double> getX() const ;
               
                void setX(const tarch::la::Vector<Dimensions,double>& x) ;
               
                double getX(int elementIndex) const ;
               
                void setX(int elementIndex, const double& x) ;
               
               /**
                * Generated
                */
                int getLevel() const ;
               
               /**
                * Generated
                */
                void setLevel(const int& level) ;
               
               /**
                * Generated
                */
               static std::string toString(const State& param);
               
               /**
                * Generated
                */
               static std::string getStateMapping();
               
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
               GridVertex convert() const;
               
               
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

#endif

