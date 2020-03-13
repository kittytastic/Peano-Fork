#ifndef _PEANO4_PARALLEL_TREEMANAGEMENTMESSAGE_H
#define _PEANO4_PARALLEL_TREEMANAGEMENTMESSAGE_H

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
      class TreeManagementMessage;
      class TreeManagementMessagePacked;
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
 * @date   13/03/2020 13:34
 */
class peano4::parallel::TreeManagementMessage { 
   
   public:
      
      typedef peano4::parallel::TreeManagementMessagePacked Packed;
      
      enum Action {
         RequestNewRemoteTree = 0, CreateNewRemoteTree = 1, RemoveChildTreeFromBooksAsChildBecameEmpty = 2, JoinWithWorker = 3, Acknowledgement = 4
      };
      
      struct PersistentRecords {
         int _masterSpacetreeId;
         int _workerSpacetreeId;
         Action _action;
         /**
          * Generated
          */
         PersistentRecords();
         
         /**
          * Generated
          */
         PersistentRecords(const int& masterSpacetreeId, const int& workerSpacetreeId, const Action& action);
         
         /**
          * Generated
          */
          int getMasterSpacetreeId() const ;
         
         /**
          * Generated
          */
          void setMasterSpacetreeId(const int& masterSpacetreeId) ;
         
         /**
          * Generated
          */
          int getWorkerSpacetreeId() const ;
         
         /**
          * Generated
          */
          void setWorkerSpacetreeId(const int& workerSpacetreeId) ;
         
         /**
          * Generated
          */
          Action getAction() const ;
         
         /**
          * Generated
          */
          void setAction(const Action& action) ;
         
         
      };
      private: 
         PersistentRecords _persistentRecords;
         
      public:
         /**
          * Generated
          */
         TreeManagementMessage();
         
         /**
          * Generated
          */
         TreeManagementMessage(const PersistentRecords& persistentRecords);
         
         /**
          * Generated
          */
         TreeManagementMessage(const int& masterSpacetreeId, const int& workerSpacetreeId, const Action& action);
         
         /**
          * Generated
          */
         virtual ~TreeManagementMessage();
         
         /**
          * Generated
          */
          int getMasterSpacetreeId() const ;
         
         /**
          * Generated
          */
          void setMasterSpacetreeId(const int& masterSpacetreeId) ;
         
         /**
          * Generated
          */
          int getWorkerSpacetreeId() const ;
         
         /**
          * Generated
          */
          void setWorkerSpacetreeId(const int& workerSpacetreeId) ;
         
         /**
          * Generated
          */
          Action getAction() const ;
         
         /**
          * Generated
          */
          void setAction(const Action& action) ;
         
         /**
          * Generated
          */
         static std::string toString(const Action& param);
         
         /**
          * Generated
          */
         static std::string getActionMapping();
         
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
         TreeManagementMessagePacked convert() const;
         
         
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
 * @date   13/03/2020 13:34
 */
class peano4::parallel::TreeManagementMessagePacked { 
   
   public:
      
      typedef peano4::parallel::TreeManagementMessage::Action Action;
      
      struct PersistentRecords {
         int _masterSpacetreeId;
         int _workerSpacetreeId;
         
         /** mapping of records:
         || Member 	|| startbit 	|| length
          |  action	| startbit 0	| #bits 3
          */
         short int _packedRecords0;
         
         /**
          * Generated
          */
         PersistentRecords();
         
         /**
          * Generated
          */
         PersistentRecords(const int& masterSpacetreeId, const int& workerSpacetreeId, const Action& action);
         
         /**
          * Generated
          */
          int getMasterSpacetreeId() const ;
         
         /**
          * Generated
          */
          void setMasterSpacetreeId(const int& masterSpacetreeId) ;
         
         /**
          * Generated
          */
          int getWorkerSpacetreeId() const ;
         
         /**
          * Generated
          */
          void setWorkerSpacetreeId(const int& workerSpacetreeId) ;
         
         /**
          * Generated
          */
          Action getAction() const ;
         
         /**
          * Generated
          */
          void setAction(const Action& action) ;
         
         
      };
      private: 
         PersistentRecords _persistentRecords;
         
      public:
         /**
          * Generated
          */
         TreeManagementMessagePacked();
         
         /**
          * Generated
          */
         TreeManagementMessagePacked(const PersistentRecords& persistentRecords);
         
         /**
          * Generated
          */
         TreeManagementMessagePacked(const int& masterSpacetreeId, const int& workerSpacetreeId, const Action& action);
         
         /**
          * Generated
          */
         virtual ~TreeManagementMessagePacked();
         
         /**
          * Generated
          */
          int getMasterSpacetreeId() const ;
         
         /**
          * Generated
          */
          void setMasterSpacetreeId(const int& masterSpacetreeId) ;
         
         /**
          * Generated
          */
          int getWorkerSpacetreeId() const ;
         
         /**
          * Generated
          */
          void setWorkerSpacetreeId(const int& workerSpacetreeId) ;
         
         /**
          * Generated
          */
          Action getAction() const ;
         
         /**
          * Generated
          */
          void setAction(const Action& action) ;
         
         /**
          * Generated
          */
         static std::string toString(const Action& param);
         
         /**
          * Generated
          */
         static std::string getActionMapping();
         
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
         TreeManagementMessage convert() const;
         
         
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

