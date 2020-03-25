#ifndef _PEANO4_GRID_GRIDCONTROLEVENT_H
#define _PEANO4_GRID_GRIDCONTROLEVENT_H

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
      class GridControlEvent;
      class GridControlEventPacked;
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
class peano4::grid::GridControlEvent { 
   
   public:
      
      typedef peano4::grid::GridControlEventPacked Packed;
      
      enum RefinementControl {
         Refine = 0, Erase = 1
      };
      
      struct PersistentRecords {
         RefinementControl _refinementControl;
         tarch::la::Vector<Dimensions,double> _offset;
         tarch::la::Vector<Dimensions,double> _width;
         tarch::la::Vector<Dimensions,double> _h;
         /**
          * Generated
          */
         PersistentRecords();
         
         /**
          * Generated
          */
         PersistentRecords(const RefinementControl& refinementControl, const tarch::la::Vector<Dimensions,double>& offset, const tarch::la::Vector<Dimensions,double>& width, const tarch::la::Vector<Dimensions,double>& h);
         
         /**
          * Generated
          */
          RefinementControl getRefinementControl() const ;
         
         /**
          * Generated
          */
          void setRefinementControl(const RefinementControl& refinementControl) ;
         
          tarch::la::Vector<Dimensions,double> getOffset() const ;
         
          void setOffset(const tarch::la::Vector<Dimensions,double>& offset) ;
         
          tarch::la::Vector<Dimensions,double> getWidth() const ;
         
          void setWidth(const tarch::la::Vector<Dimensions,double>& width) ;
         
          tarch::la::Vector<Dimensions,double> getH() const ;
         
          void setH(const tarch::la::Vector<Dimensions,double>& h) ;
         
         
      };
      private: 
         PersistentRecords _persistentRecords;
         
      public:
         /**
          * Generated
          */
         GridControlEvent();
         
         /**
          * Generated
          */
         GridControlEvent(const PersistentRecords& persistentRecords);
         
         /**
          * Generated
          */
         GridControlEvent(const RefinementControl& refinementControl, const tarch::la::Vector<Dimensions,double>& offset, const tarch::la::Vector<Dimensions,double>& width, const tarch::la::Vector<Dimensions,double>& h);
         
         /**
          * Generated
          */
         ~GridControlEvent();
         
         /**
          * Generated
          */
          RefinementControl getRefinementControl() const ;
         
         /**
          * Generated
          */
          void setRefinementControl(const RefinementControl& refinementControl) ;
         
          tarch::la::Vector<Dimensions,double> getOffset() const ;
         
          void setOffset(const tarch::la::Vector<Dimensions,double>& offset) ;
         
          double getOffset(int elementIndex) const ;
         
          void setOffset(int elementIndex, const double& offset) ;
         
          tarch::la::Vector<Dimensions,double> getWidth() const ;
         
          void setWidth(const tarch::la::Vector<Dimensions,double>& width) ;
         
          double getWidth(int elementIndex) const ;
         
          void setWidth(int elementIndex, const double& width) ;
         
          tarch::la::Vector<Dimensions,double> getH() const ;
         
          void setH(const tarch::la::Vector<Dimensions,double>& h) ;
         
          double getH(int elementIndex) const ;
         
          void setH(int elementIndex, const double& h) ;
         
         /**
          * Generated
          */
         static std::string toString(const RefinementControl& param);
         
         /**
          * Generated
          */
         static std::string getRefinementControlMapping();
         
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
         GridControlEventPacked convert() const;
         
         
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
class peano4::grid::GridControlEventPacked { 
   
   public:
      
      typedef peano4::grid::GridControlEvent::RefinementControl RefinementControl;
      
      struct PersistentRecords {
         RefinementControl _refinementControl;
         tarch::la::Vector<Dimensions,double> _offset;
         tarch::la::Vector<Dimensions,double> _width;
         tarch::la::Vector<Dimensions,double> _h;
         /**
          * Generated
          */
         PersistentRecords();
         
         /**
          * Generated
          */
         PersistentRecords(const RefinementControl& refinementControl, const tarch::la::Vector<Dimensions,double>& offset, const tarch::la::Vector<Dimensions,double>& width, const tarch::la::Vector<Dimensions,double>& h);
         
         /**
          * Generated
          */
          RefinementControl getRefinementControl() const ;
         
         /**
          * Generated
          */
          void setRefinementControl(const RefinementControl& refinementControl) ;
         
          tarch::la::Vector<Dimensions,double> getOffset() const ;
         
          void setOffset(const tarch::la::Vector<Dimensions,double>& offset) ;
         
          tarch::la::Vector<Dimensions,double> getWidth() const ;
         
          void setWidth(const tarch::la::Vector<Dimensions,double>& width) ;
         
          tarch::la::Vector<Dimensions,double> getH() const ;
         
          void setH(const tarch::la::Vector<Dimensions,double>& h) ;
         
         
      };
      private: 
         PersistentRecords _persistentRecords;
         
      public:
         /**
          * Generated
          */
         GridControlEventPacked();
         
         /**
          * Generated
          */
         GridControlEventPacked(const PersistentRecords& persistentRecords);
         
         /**
          * Generated
          */
         GridControlEventPacked(const RefinementControl& refinementControl, const tarch::la::Vector<Dimensions,double>& offset, const tarch::la::Vector<Dimensions,double>& width, const tarch::la::Vector<Dimensions,double>& h);
         
         /**
          * Generated
          */
         ~GridControlEventPacked();
         
         /**
          * Generated
          */
          RefinementControl getRefinementControl() const ;
         
         /**
          * Generated
          */
          void setRefinementControl(const RefinementControl& refinementControl) ;
         
          tarch::la::Vector<Dimensions,double> getOffset() const ;
         
          void setOffset(const tarch::la::Vector<Dimensions,double>& offset) ;
         
          double getOffset(int elementIndex) const ;
         
          void setOffset(int elementIndex, const double& offset) ;
         
          tarch::la::Vector<Dimensions,double> getWidth() const ;
         
          void setWidth(const tarch::la::Vector<Dimensions,double>& width) ;
         
          double getWidth(int elementIndex) const ;
         
          void setWidth(int elementIndex, const double& width) ;
         
          tarch::la::Vector<Dimensions,double> getH() const ;
         
          void setH(const tarch::la::Vector<Dimensions,double>& h) ;
         
          double getH(int elementIndex) const ;
         
          void setH(int elementIndex, const double& h) ;
         
         /**
          * Generated
          */
         static std::string toString(const RefinementControl& param);
         
         /**
          * Generated
          */
         static std::string getRefinementControlMapping();
         
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
         GridControlEvent convert() const;
         
         
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

