#ifndef _PEANO4_PARALLEL_STARTTRAVERSALMESSAGE_H
#define _PEANO4_PARALLEL_STARTTRAVERSALMESSAGE_H

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
   namespace parallel {
      class StartTraversalMessage;
      class StartTraversalMessagePacked;
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
 * @date   16/01/2019 19:35
 */
class peano4::parallel::StartTraversalMessage { 
   
   public:
      
      typedef peano4::parallel::StartTraversalMessagePacked Packed;
      
      struct PersistentRecords {
         int _stepIdentifier;
         /**
          * Generated
          */
         PersistentRecords();
         
         /**
          * Generated
          */
         PersistentRecords(const int& stepIdentifier);
         
         /**
          * Generated
          */
          int getStepIdentifier() const ;
         
         /**
          * Generated
          */
          void setStepIdentifier(const int& stepIdentifier) ;
         
         
      };
      private: 
         PersistentRecords _persistentRecords;
         
      public:
         /**
          * Generated
          */
         StartTraversalMessage();
         
         /**
          * Generated
          */
         StartTraversalMessage(const PersistentRecords& persistentRecords);
         
         /**
          * Generated
          */
         StartTraversalMessage(const int& stepIdentifier);
         
         /**
          * Generated
          */
         virtual ~StartTraversalMessage();
         
         /**
          * Generated
          */
          int getStepIdentifier() const ;
         
         /**
          * Generated
          */
          void setStepIdentifier(const int& stepIdentifier) ;
         
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
         StartTraversalMessagePacked convert() const;
         
         
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
 * @date   16/01/2019 19:35
 */
class peano4::parallel::StartTraversalMessagePacked { 
   
   public:
      
      struct PersistentRecords {
         int _stepIdentifier;
         /**
          * Generated
          */
         PersistentRecords();
         
         /**
          * Generated
          */
         PersistentRecords(const int& stepIdentifier);
         
         /**
          * Generated
          */
          int getStepIdentifier() const ;
         
         /**
          * Generated
          */
          void setStepIdentifier(const int& stepIdentifier) ;
         
         
      };
      private: 
         PersistentRecords _persistentRecords;
         
      public:
         /**
          * Generated
          */
         StartTraversalMessagePacked();
         
         /**
          * Generated
          */
         StartTraversalMessagePacked(const PersistentRecords& persistentRecords);
         
         /**
          * Generated
          */
         StartTraversalMessagePacked(const int& stepIdentifier);
         
         /**
          * Generated
          */
         virtual ~StartTraversalMessagePacked();
         
         /**
          * Generated
          */
          int getStepIdentifier() const ;
         
         /**
          * Generated
          */
          void setStepIdentifier(const int& stepIdentifier) ;
         
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
         StartTraversalMessage convert() const;
         
         
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

