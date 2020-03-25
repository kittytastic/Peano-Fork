#ifndef _PEANO4_GRID_AUTOMATONSTATE_H
#define _PEANO4_GRID_AUTOMATONSTATE_H

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
      class AutomatonState;
      class AutomatonStatePacked;
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
 * @date   22/03/2020 16:48
 */
class peano4::grid::AutomatonState { 
   
   public:
      
      typedef peano4::grid::AutomatonStatePacked Packed;
      
      struct PersistentRecords {
         int _level;
         tarch::la::Vector<Dimensions,double> _x;
         tarch::la::Vector<Dimensions,double> _h;
         bool _inverted;
         std::bitset<Dimensions> _evenFlags;
         tarch::la::Vector<DimensionsTimesTwo,short int> _accessNumber;
         /**
          * Generated
          */
         PersistentRecords();
         
         /**
          * Generated
          */
         PersistentRecords(const int& level, const tarch::la::Vector<Dimensions,double>& x, const tarch::la::Vector<Dimensions,double>& h, const bool& inverted, const std::bitset<Dimensions>& evenFlags, const tarch::la::Vector<DimensionsTimesTwo,short int>& accessNumber);
         
         /**
          * Generated
          */
          int getLevel() const ;
         
         /**
          * Generated
          */
          void setLevel(const int& level) ;
         
          tarch::la::Vector<Dimensions,double> getX() const ;
         
          void setX(const tarch::la::Vector<Dimensions,double>& x) ;
         
          tarch::la::Vector<Dimensions,double> getH() const ;
         
          void setH(const tarch::la::Vector<Dimensions,double>& h) ;
         
         /**
          * Generated
          */
          bool getInverted() const ;
         
         /**
          * Generated
          */
          void setInverted(const bool& inverted) ;
         
          std::bitset<Dimensions> getEvenFlags() const ;
         
          void setEvenFlags(const std::bitset<Dimensions>& evenFlags) ;
         
          tarch::la::Vector<DimensionsTimesTwo,short int> getAccessNumber() const ;
         
          void setAccessNumber(const tarch::la::Vector<DimensionsTimesTwo,short int>& accessNumber) ;
         
         
      };
      private: 
         PersistentRecords _persistentRecords;
         
      public:
         /**
          * Generated
          */
         AutomatonState();
         
         /**
          * Generated
          */
         AutomatonState(const PersistentRecords& persistentRecords);
         
         /**
          * Generated
          */
         AutomatonState(const int& level, const tarch::la::Vector<Dimensions,double>& x, const tarch::la::Vector<Dimensions,double>& h, const bool& inverted, const std::bitset<Dimensions>& evenFlags, const tarch::la::Vector<DimensionsTimesTwo,short int>& accessNumber);
         
         /**
          * Generated
          */
         ~AutomatonState();
         
         /**
          * Generated
          */
          int getLevel() const ;
         
         /**
          * Generated
          */
          void setLevel(const int& level) ;
         
          tarch::la::Vector<Dimensions,double> getX() const ;
         
          void setX(const tarch::la::Vector<Dimensions,double>& x) ;
         
          double getX(int elementIndex) const ;
         
          void setX(int elementIndex, const double& x) ;
         
          tarch::la::Vector<Dimensions,double> getH() const ;
         
          void setH(const tarch::la::Vector<Dimensions,double>& h) ;
         
          double getH(int elementIndex) const ;
         
          void setH(int elementIndex, const double& h) ;
         
         /**
          * Generated
          */
          bool getInverted() const ;
         
         /**
          * Generated
          */
          void setInverted(const bool& inverted) ;
         
          std::bitset<Dimensions> getEvenFlags() const ;
         
          void setEvenFlags(const std::bitset<Dimensions>& evenFlags) ;
         
          bool getEvenFlags(int elementIndex) const ;
         
          void setEvenFlags(int elementIndex, const bool& evenFlags) ;
         
          void flipEvenFlags(int elementIndex) ;
         
          tarch::la::Vector<DimensionsTimesTwo,short int> getAccessNumber() const ;
         
          void setAccessNumber(const tarch::la::Vector<DimensionsTimesTwo,short int>& accessNumber) ;
         
          short int getAccessNumber(int elementIndex) const ;
         
          void setAccessNumber(int elementIndex, const short int& accessNumber) ;
         
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
         AutomatonStatePacked convert() const;
         
         
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
            
            static bool isMessageInQueue(int tag);
            
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
 * @date   22/03/2020 16:48
 */
class peano4::grid::AutomatonStatePacked { 
   
   public:
      
      struct PersistentRecords {
         int _level;
         tarch::la::Vector<Dimensions,double> _x;
         tarch::la::Vector<Dimensions,double> _h;
         tarch::la::Vector<DimensionsTimesTwo,short int> _accessNumber;
         
         /** mapping of records:
         || Member 	|| startbit 	|| length
          |  inverted	| startbit 0	| #bits 1
          |  evenFlags	| startbit 1	| #bits Dimensions
          */
         short int _packedRecords0;
         
         /**
          * Generated
          */
         PersistentRecords();
         
         /**
          * Generated
          */
         PersistentRecords(const int& level, const tarch::la::Vector<Dimensions,double>& x, const tarch::la::Vector<Dimensions,double>& h, const bool& inverted, const std::bitset<Dimensions>& evenFlags, const tarch::la::Vector<DimensionsTimesTwo,short int>& accessNumber);
         
         /**
          * Generated
          */
          int getLevel() const ;
         
         /**
          * Generated
          */
          void setLevel(const int& level) ;
         
          tarch::la::Vector<Dimensions,double> getX() const ;
         
          void setX(const tarch::la::Vector<Dimensions,double>& x) ;
         
          tarch::la::Vector<Dimensions,double> getH() const ;
         
          void setH(const tarch::la::Vector<Dimensions,double>& h) ;
         
         /**
          * Generated
          */
          bool getInverted() const ;
         
         /**
          * Generated
          */
          void setInverted(const bool& inverted) ;
         
          std::bitset<Dimensions> getEvenFlags() const ;
         
          void setEvenFlags(const std::bitset<Dimensions>& evenFlags) ;
         
          tarch::la::Vector<DimensionsTimesTwo,short int> getAccessNumber() const ;
         
          void setAccessNumber(const tarch::la::Vector<DimensionsTimesTwo,short int>& accessNumber) ;
         
         
      };
      private: 
         PersistentRecords _persistentRecords;
         
      public:
         /**
          * Generated
          */
         AutomatonStatePacked();
         
         /**
          * Generated
          */
         AutomatonStatePacked(const PersistentRecords& persistentRecords);
         
         /**
          * Generated
          */
         AutomatonStatePacked(const int& level, const tarch::la::Vector<Dimensions,double>& x, const tarch::la::Vector<Dimensions,double>& h, const bool& inverted, const std::bitset<Dimensions>& evenFlags, const tarch::la::Vector<DimensionsTimesTwo,short int>& accessNumber);
         
         /**
          * Generated
          */
         ~AutomatonStatePacked();
         
         /**
          * Generated
          */
          int getLevel() const ;
         
         /**
          * Generated
          */
          void setLevel(const int& level) ;
         
          tarch::la::Vector<Dimensions,double> getX() const ;
         
          void setX(const tarch::la::Vector<Dimensions,double>& x) ;
         
          double getX(int elementIndex) const ;
         
          void setX(int elementIndex, const double& x) ;
         
          tarch::la::Vector<Dimensions,double> getH() const ;
         
          void setH(const tarch::la::Vector<Dimensions,double>& h) ;
         
          double getH(int elementIndex) const ;
         
          void setH(int elementIndex, const double& h) ;
         
         /**
          * Generated
          */
          bool getInverted() const ;
         
         /**
          * Generated
          */
          void setInverted(const bool& inverted) ;
         
          std::bitset<Dimensions> getEvenFlags() const ;
         
          void setEvenFlags(const std::bitset<Dimensions>& evenFlags) ;
         
          bool getEvenFlags(int elementIndex) const ;
         
          void setEvenFlags(int elementIndex, const bool& evenFlags) ;
         
          void flipEvenFlags(int elementIndex) ;
         
          tarch::la::Vector<DimensionsTimesTwo,short int> getAccessNumber() const ;
         
          void setAccessNumber(const tarch::la::Vector<DimensionsTimesTwo,short int>& accessNumber) ;
         
          short int getAccessNumber(int elementIndex) const ;
         
          void setAccessNumber(int elementIndex, const short int& accessNumber) ;
         
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
         AutomatonState convert() const;
         
         
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
            
            static bool isMessageInQueue(int tag);
            
            int getSenderRank() const;
            #endif
   
};

#endif

