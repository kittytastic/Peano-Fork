#ifndef _PEANO4_GRID_GRIDTRAVERSALEVENT_H
#define _PEANO4_GRID_GRIDTRAVERSALEVENT_H

#include "peano4/utils/Globals.h"
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
      class GridTraversalEvent;
      class GridTraversalEventPacked;
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
class peano4::grid::GridTraversalEvent { 
   
   public:
      
      typedef peano4::grid::GridTraversalEventPacked Packed;
      
      enum DataExchangeType {
         ExchangeHorizontally = 0, StreamInOut = 1, ExchangeVerticallyWithMaster = 2, ExchangeVerticallyWithWorker = 3, None = 4
      };
      
      struct PersistentRecords {
         tarch::la::Vector<Dimensions,double> _x;
         tarch::la::Vector<Dimensions,double> _h;
         bool _isRefined;
         tarch::la::Vector<TwoPowerD,int> _vertexDataFrom;
         tarch::la::Vector<TwoPowerD,int> _vertexDataTo;
         tarch::la::Vector<TwoTimesD,int> _faceDataFrom;
         tarch::la::Vector<TwoTimesD,int> _faceDataTo;
         int _cellData;
         tarch::la::Vector<TwoPowerD,DataExchangeType> _sendReceiveVertexData;
         tarch::la::Vector<TwoTimesD,DataExchangeType> _sendReceiveFaceData;
         DataExchangeType _sendReceiveCellData;
         tarch::la::Vector<TwoPowerD,int> _sendReceiveVertexDataRank;
         tarch::la::Vector<TwoTimesD,int> _sendReceiveFaceDataRank;
         int _sendReceiveCellDataRank;
         tarch::la::Vector<Dimensions,int> _relativePositionToFather;
         /**
          * Generated
          */
         PersistentRecords();
         
         /**
          * Generated
          */
         PersistentRecords(const tarch::la::Vector<Dimensions,double>& x, const tarch::la::Vector<Dimensions,double>& h, const bool& isRefined, const tarch::la::Vector<TwoPowerD,int>& vertexDataFrom, const tarch::la::Vector<TwoPowerD,int>& vertexDataTo, const tarch::la::Vector<TwoTimesD,int>& faceDataFrom, const tarch::la::Vector<TwoTimesD,int>& faceDataTo, const int& cellData, const tarch::la::Vector<TwoPowerD,DataExchangeType>& sendReceiveVertexData, const tarch::la::Vector<TwoTimesD,DataExchangeType>& sendReceiveFaceData, const DataExchangeType& sendReceiveCellData, const tarch::la::Vector<TwoPowerD,int>& sendReceiveVertexDataRank, const tarch::la::Vector<TwoTimesD,int>& sendReceiveFaceDataRank, const int& sendReceiveCellDataRank, const tarch::la::Vector<Dimensions,int>& relativePositionToFather);
         
          tarch::la::Vector<Dimensions,double> getX() const ;
         
          void setX(const tarch::la::Vector<Dimensions,double>& x) ;
         
          tarch::la::Vector<Dimensions,double> getH() const ;
         
          void setH(const tarch::la::Vector<Dimensions,double>& h) ;
         
         /**
          * Generated
          */
          bool getIsRefined() const ;
         
         /**
          * Generated
          */
          void setIsRefined(const bool& isRefined) ;
         
          tarch::la::Vector<TwoPowerD,int> getVertexDataFrom() const ;
         
          void setVertexDataFrom(const tarch::la::Vector<TwoPowerD,int>& vertexDataFrom) ;
         
          tarch::la::Vector<TwoPowerD,int> getVertexDataTo() const ;
         
          void setVertexDataTo(const tarch::la::Vector<TwoPowerD,int>& vertexDataTo) ;
         
          tarch::la::Vector<TwoTimesD,int> getFaceDataFrom() const ;
         
          void setFaceDataFrom(const tarch::la::Vector<TwoTimesD,int>& faceDataFrom) ;
         
          tarch::la::Vector<TwoTimesD,int> getFaceDataTo() const ;
         
          void setFaceDataTo(const tarch::la::Vector<TwoTimesD,int>& faceDataTo) ;
         
         /**
          * Generated
          */
          int getCellData() const ;
         
         /**
          * Generated
          */
          void setCellData(const int& cellData) ;
         
          tarch::la::Vector<TwoPowerD,DataExchangeType> getSendReceiveVertexData() const ;
         
          void setSendReceiveVertexData(const tarch::la::Vector<TwoPowerD,DataExchangeType>& sendReceiveVertexData) ;
         
          tarch::la::Vector<TwoTimesD,DataExchangeType> getSendReceiveFaceData() const ;
         
          void setSendReceiveFaceData(const tarch::la::Vector<TwoTimesD,DataExchangeType>& sendReceiveFaceData) ;
         
         /**
          * Generated
          */
          DataExchangeType getSendReceiveCellData() const ;
         
         /**
          * Generated
          */
          void setSendReceiveCellData(const DataExchangeType& sendReceiveCellData) ;
         
          tarch::la::Vector<TwoPowerD,int> getSendReceiveVertexDataRank() const ;
         
          void setSendReceiveVertexDataRank(const tarch::la::Vector<TwoPowerD,int>& sendReceiveVertexDataRank) ;
         
          tarch::la::Vector<TwoTimesD,int> getSendReceiveFaceDataRank() const ;
         
          void setSendReceiveFaceDataRank(const tarch::la::Vector<TwoTimesD,int>& sendReceiveFaceDataRank) ;
         
         /**
          * Generated
          */
          int getSendReceiveCellDataRank() const ;
         
         /**
          * Generated
          */
          void setSendReceiveCellDataRank(const int& sendReceiveCellDataRank) ;
         
          tarch::la::Vector<Dimensions,int> getRelativePositionToFather() const ;
         
          void setRelativePositionToFather(const tarch::la::Vector<Dimensions,int>& relativePositionToFather) ;
         
         
      };
      private: 
         PersistentRecords _persistentRecords;
         
      public:
         /**
          * Generated
          */
         GridTraversalEvent();
         
         /**
          * Generated
          */
         GridTraversalEvent(const PersistentRecords& persistentRecords);
         
         /**
          * Generated
          */
         GridTraversalEvent(const tarch::la::Vector<Dimensions,double>& x, const tarch::la::Vector<Dimensions,double>& h, const bool& isRefined, const tarch::la::Vector<TwoPowerD,int>& vertexDataFrom, const tarch::la::Vector<TwoPowerD,int>& vertexDataTo, const tarch::la::Vector<TwoTimesD,int>& faceDataFrom, const tarch::la::Vector<TwoTimesD,int>& faceDataTo, const int& cellData, const tarch::la::Vector<TwoPowerD,DataExchangeType>& sendReceiveVertexData, const tarch::la::Vector<TwoTimesD,DataExchangeType>& sendReceiveFaceData, const DataExchangeType& sendReceiveCellData, const tarch::la::Vector<TwoPowerD,int>& sendReceiveVertexDataRank, const tarch::la::Vector<TwoTimesD,int>& sendReceiveFaceDataRank, const int& sendReceiveCellDataRank, const tarch::la::Vector<Dimensions,int>& relativePositionToFather);
         
         /**
          * Generated
          */
         virtual ~GridTraversalEvent();
         
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
          bool getIsRefined() const ;
         
         /**
          * Generated
          */
          void setIsRefined(const bool& isRefined) ;
         
          tarch::la::Vector<TwoPowerD,int> getVertexDataFrom() const ;
         
          void setVertexDataFrom(const tarch::la::Vector<TwoPowerD,int>& vertexDataFrom) ;
         
          int getVertexDataFrom(int elementIndex) const ;
         
          void setVertexDataFrom(int elementIndex, const int& vertexDataFrom) ;
         
          tarch::la::Vector<TwoPowerD,int> getVertexDataTo() const ;
         
          void setVertexDataTo(const tarch::la::Vector<TwoPowerD,int>& vertexDataTo) ;
         
          int getVertexDataTo(int elementIndex) const ;
         
          void setVertexDataTo(int elementIndex, const int& vertexDataTo) ;
         
          tarch::la::Vector<TwoTimesD,int> getFaceDataFrom() const ;
         
          void setFaceDataFrom(const tarch::la::Vector<TwoTimesD,int>& faceDataFrom) ;
         
          int getFaceDataFrom(int elementIndex) const ;
         
          void setFaceDataFrom(int elementIndex, const int& faceDataFrom) ;
         
          tarch::la::Vector<TwoTimesD,int> getFaceDataTo() const ;
         
          void setFaceDataTo(const tarch::la::Vector<TwoTimesD,int>& faceDataTo) ;
         
          int getFaceDataTo(int elementIndex) const ;
         
          void setFaceDataTo(int elementIndex, const int& faceDataTo) ;
         
         /**
          * Generated
          */
          int getCellData() const ;
         
         /**
          * Generated
          */
          void setCellData(const int& cellData) ;
         
          tarch::la::Vector<TwoPowerD,DataExchangeType> getSendReceiveVertexData() const ;
         
          void setSendReceiveVertexData(const tarch::la::Vector<TwoPowerD,DataExchangeType>& sendReceiveVertexData) ;
         
          peano4::grid::GridTraversalEvent::DataExchangeType getSendReceiveVertexData(int elementIndex) const ;
         
          void setSendReceiveVertexData(int elementIndex, const DataExchangeType& sendReceiveVertexData) ;
         
          tarch::la::Vector<TwoTimesD,DataExchangeType> getSendReceiveFaceData() const ;
         
          void setSendReceiveFaceData(const tarch::la::Vector<TwoTimesD,DataExchangeType>& sendReceiveFaceData) ;
         
          peano4::grid::GridTraversalEvent::DataExchangeType getSendReceiveFaceData(int elementIndex) const ;
         
          void setSendReceiveFaceData(int elementIndex, const DataExchangeType& sendReceiveFaceData) ;
         
         /**
          * Generated
          */
          DataExchangeType getSendReceiveCellData() const ;
         
         /**
          * Generated
          */
          void setSendReceiveCellData(const DataExchangeType& sendReceiveCellData) ;
         
          tarch::la::Vector<TwoPowerD,int> getSendReceiveVertexDataRank() const ;
         
          void setSendReceiveVertexDataRank(const tarch::la::Vector<TwoPowerD,int>& sendReceiveVertexDataRank) ;
         
          int getSendReceiveVertexDataRank(int elementIndex) const ;
         
          void setSendReceiveVertexDataRank(int elementIndex, const int& sendReceiveVertexDataRank) ;
         
          tarch::la::Vector<TwoTimesD,int> getSendReceiveFaceDataRank() const ;
         
          void setSendReceiveFaceDataRank(const tarch::la::Vector<TwoTimesD,int>& sendReceiveFaceDataRank) ;
         
          int getSendReceiveFaceDataRank(int elementIndex) const ;
         
          void setSendReceiveFaceDataRank(int elementIndex, const int& sendReceiveFaceDataRank) ;
         
         /**
          * Generated
          */
          int getSendReceiveCellDataRank() const ;
         
         /**
          * Generated
          */
          void setSendReceiveCellDataRank(const int& sendReceiveCellDataRank) ;
         
          tarch::la::Vector<Dimensions,int> getRelativePositionToFather() const ;
         
          void setRelativePositionToFather(const tarch::la::Vector<Dimensions,int>& relativePositionToFather) ;
         
          int getRelativePositionToFather(int elementIndex) const ;
         
          void setRelativePositionToFather(int elementIndex, const int& relativePositionToFather) ;
         
         /**
          * Generated
          */
         static std::string toString(const DataExchangeType& param);
         
         /**
          * Generated
          */
         static std::string getDataExchangeTypeMapping();
         
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
         GridTraversalEventPacked convert() const;
         
         
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
class peano4::grid::GridTraversalEventPacked { 
   
   public:
      
      typedef peano4::grid::GridTraversalEvent::DataExchangeType DataExchangeType;
      
      struct PersistentRecords {
         tarch::la::Vector<Dimensions,double> _x;
         tarch::la::Vector<Dimensions,double> _h;
         tarch::la::Vector<TwoPowerD,int> _sendReceiveVertexDataRank;
         tarch::la::Vector<TwoTimesD,int> _sendReceiveFaceDataRank;
         int _sendReceiveCellDataRank;
         tarch::la::Vector<Dimensions,int> _relativePositionToFather;
         
         /** mapping of records:
         || Member 	|| startbit 	|| length
          |  isRefined	| startbit 0	| #bits 1
          |  faceDataFrom	| startbit 1	| #bits 24
          |  faceDataTo	| startbit 25	| #bits 24
          |  cellData	| startbit 49	| #bits 3
          |  sendReceiveCellData	| startbit 52	| #bits 3
          */
         long int _packedRecords0;
         
         
         /** mapping of records:
         || Member 	|| startbit 	|| length
          |  vertexDataFrom	| startbit 0	| #bits 64
          */
         long int _packedRecords1;
         
         
         /** mapping of records:
         || Member 	|| startbit 	|| length
          |  vertexDataTo	| startbit 0	| #bits 64
          */
         long int _packedRecords2;
         
         
         /** mapping of records:
         || Member 	|| startbit 	|| length
          |  sendReceiveVertexData	| startbit 0	| #bits 48
          */
         long int _packedRecords3;
         
         
         /** mapping of records:
         || Member 	|| startbit 	|| length
          |  sendReceiveFaceData	| startbit 0	| #bits 18
          */
         long int _packedRecords4;
         
         /**
          * Generated
          */
         PersistentRecords();
         
         /**
          * Generated
          */
         PersistentRecords(const tarch::la::Vector<Dimensions,double>& x, const tarch::la::Vector<Dimensions,double>& h, const bool& isRefined, const tarch::la::Vector<TwoPowerD,int>& vertexDataFrom, const tarch::la::Vector<TwoPowerD,int>& vertexDataTo, const tarch::la::Vector<TwoTimesD,int>& faceDataFrom, const tarch::la::Vector<TwoTimesD,int>& faceDataTo, const int& cellData, const tarch::la::Vector<TwoPowerD,DataExchangeType>& sendReceiveVertexData, const tarch::la::Vector<TwoTimesD,DataExchangeType>& sendReceiveFaceData, const DataExchangeType& sendReceiveCellData, const tarch::la::Vector<TwoPowerD,int>& sendReceiveVertexDataRank, const tarch::la::Vector<TwoTimesD,int>& sendReceiveFaceDataRank, const int& sendReceiveCellDataRank, const tarch::la::Vector<Dimensions,int>& relativePositionToFather);
         
          tarch::la::Vector<Dimensions,double> getX() const ;
         
          void setX(const tarch::la::Vector<Dimensions,double>& x) ;
         
          tarch::la::Vector<Dimensions,double> getH() const ;
         
          void setH(const tarch::la::Vector<Dimensions,double>& h) ;
         
         /**
          * Generated
          */
          bool getIsRefined() const ;
         
         /**
          * Generated
          */
          void setIsRefined(const bool& isRefined) ;
         
          tarch::la::Vector<TwoPowerD,int> getVertexDataFrom() const ;
         
          void setVertexDataFrom(const tarch::la::Vector<TwoPowerD,int>& vertexDataFrom) ;
         
          tarch::la::Vector<TwoPowerD,int> getVertexDataTo() const ;
         
          void setVertexDataTo(const tarch::la::Vector<TwoPowerD,int>& vertexDataTo) ;
         
          tarch::la::Vector<TwoTimesD,int> getFaceDataFrom() const ;
         
          void setFaceDataFrom(const tarch::la::Vector<TwoTimesD,int>& faceDataFrom) ;
         
          tarch::la::Vector<TwoTimesD,int> getFaceDataTo() const ;
         
          void setFaceDataTo(const tarch::la::Vector<TwoTimesD,int>& faceDataTo) ;
         
         /**
          * Generated
          */
          int getCellData() const ;
         
         /**
          * Generated
          */
          void setCellData(const int& cellData) ;
         
          tarch::la::Vector<TwoPowerD,DataExchangeType> getSendReceiveVertexData() const ;
         
          void setSendReceiveVertexData(const tarch::la::Vector<TwoPowerD,DataExchangeType>& sendReceiveVertexData) ;
         
          tarch::la::Vector<TwoTimesD,DataExchangeType> getSendReceiveFaceData() const ;
         
          void setSendReceiveFaceData(const tarch::la::Vector<TwoTimesD,DataExchangeType>& sendReceiveFaceData) ;
         
         /**
          * Generated
          */
          DataExchangeType getSendReceiveCellData() const ;
         
         /**
          * Generated
          */
          void setSendReceiveCellData(const DataExchangeType& sendReceiveCellData) ;
         
          tarch::la::Vector<TwoPowerD,int> getSendReceiveVertexDataRank() const ;
         
          void setSendReceiveVertexDataRank(const tarch::la::Vector<TwoPowerD,int>& sendReceiveVertexDataRank) ;
         
          tarch::la::Vector<TwoTimesD,int> getSendReceiveFaceDataRank() const ;
         
          void setSendReceiveFaceDataRank(const tarch::la::Vector<TwoTimesD,int>& sendReceiveFaceDataRank) ;
         
         /**
          * Generated
          */
          int getSendReceiveCellDataRank() const ;
         
         /**
          * Generated
          */
          void setSendReceiveCellDataRank(const int& sendReceiveCellDataRank) ;
         
          tarch::la::Vector<Dimensions,int> getRelativePositionToFather() const ;
         
          void setRelativePositionToFather(const tarch::la::Vector<Dimensions,int>& relativePositionToFather) ;
         
         
      };
      private: 
         PersistentRecords _persistentRecords;
         
      public:
         /**
          * Generated
          */
         GridTraversalEventPacked();
         
         /**
          * Generated
          */
         GridTraversalEventPacked(const PersistentRecords& persistentRecords);
         
         /**
          * Generated
          */
         GridTraversalEventPacked(const tarch::la::Vector<Dimensions,double>& x, const tarch::la::Vector<Dimensions,double>& h, const bool& isRefined, const tarch::la::Vector<TwoPowerD,int>& vertexDataFrom, const tarch::la::Vector<TwoPowerD,int>& vertexDataTo, const tarch::la::Vector<TwoTimesD,int>& faceDataFrom, const tarch::la::Vector<TwoTimesD,int>& faceDataTo, const int& cellData, const tarch::la::Vector<TwoPowerD,DataExchangeType>& sendReceiveVertexData, const tarch::la::Vector<TwoTimesD,DataExchangeType>& sendReceiveFaceData, const DataExchangeType& sendReceiveCellData, const tarch::la::Vector<TwoPowerD,int>& sendReceiveVertexDataRank, const tarch::la::Vector<TwoTimesD,int>& sendReceiveFaceDataRank, const int& sendReceiveCellDataRank, const tarch::la::Vector<Dimensions,int>& relativePositionToFather);
         
         /**
          * Generated
          */
         virtual ~GridTraversalEventPacked();
         
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
          bool getIsRefined() const ;
         
         /**
          * Generated
          */
          void setIsRefined(const bool& isRefined) ;
         
          tarch::la::Vector<TwoPowerD,int> getVertexDataFrom() const ;
         
          void setVertexDataFrom(const tarch::la::Vector<TwoPowerD,int>& vertexDataFrom) ;
         
          int getVertexDataFrom(int elementIndex) const ;
         
          void setVertexDataFrom(int elementIndex, const int& vertexDataFrom) ;
         
          tarch::la::Vector<TwoPowerD,int> getVertexDataTo() const ;
         
          void setVertexDataTo(const tarch::la::Vector<TwoPowerD,int>& vertexDataTo) ;
         
          int getVertexDataTo(int elementIndex) const ;
         
          void setVertexDataTo(int elementIndex, const int& vertexDataTo) ;
         
          tarch::la::Vector<TwoTimesD,int> getFaceDataFrom() const ;
         
          void setFaceDataFrom(const tarch::la::Vector<TwoTimesD,int>& faceDataFrom) ;
         
          int getFaceDataFrom(int elementIndex) const ;
         
          void setFaceDataFrom(int elementIndex, const int& faceDataFrom) ;
         
          tarch::la::Vector<TwoTimesD,int> getFaceDataTo() const ;
         
          void setFaceDataTo(const tarch::la::Vector<TwoTimesD,int>& faceDataTo) ;
         
          int getFaceDataTo(int elementIndex) const ;
         
          void setFaceDataTo(int elementIndex, const int& faceDataTo) ;
         
         /**
          * Generated
          */
          int getCellData() const ;
         
         /**
          * Generated
          */
          void setCellData(const int& cellData) ;
         
          tarch::la::Vector<TwoPowerD,DataExchangeType> getSendReceiveVertexData() const ;
         
          void setSendReceiveVertexData(const tarch::la::Vector<TwoPowerD,DataExchangeType>& sendReceiveVertexData) ;
         
          peano4::grid::GridTraversalEvent::DataExchangeType getSendReceiveVertexData(int elementIndex) const ;
         
          void setSendReceiveVertexData(int elementIndex, const DataExchangeType& sendReceiveVertexData) ;
         
          tarch::la::Vector<TwoTimesD,DataExchangeType> getSendReceiveFaceData() const ;
         
          void setSendReceiveFaceData(const tarch::la::Vector<TwoTimesD,DataExchangeType>& sendReceiveFaceData) ;
         
          peano4::grid::GridTraversalEvent::DataExchangeType getSendReceiveFaceData(int elementIndex) const ;
         
          void setSendReceiveFaceData(int elementIndex, const DataExchangeType& sendReceiveFaceData) ;
         
         /**
          * Generated
          */
          DataExchangeType getSendReceiveCellData() const ;
         
         /**
          * Generated
          */
          void setSendReceiveCellData(const DataExchangeType& sendReceiveCellData) ;
         
          tarch::la::Vector<TwoPowerD,int> getSendReceiveVertexDataRank() const ;
         
          void setSendReceiveVertexDataRank(const tarch::la::Vector<TwoPowerD,int>& sendReceiveVertexDataRank) ;
         
          int getSendReceiveVertexDataRank(int elementIndex) const ;
         
          void setSendReceiveVertexDataRank(int elementIndex, const int& sendReceiveVertexDataRank) ;
         
          tarch::la::Vector<TwoTimesD,int> getSendReceiveFaceDataRank() const ;
         
          void setSendReceiveFaceDataRank(const tarch::la::Vector<TwoTimesD,int>& sendReceiveFaceDataRank) ;
         
          int getSendReceiveFaceDataRank(int elementIndex) const ;
         
          void setSendReceiveFaceDataRank(int elementIndex, const int& sendReceiveFaceDataRank) ;
         
         /**
          * Generated
          */
          int getSendReceiveCellDataRank() const ;
         
         /**
          * Generated
          */
          void setSendReceiveCellDataRank(const int& sendReceiveCellDataRank) ;
         
          tarch::la::Vector<Dimensions,int> getRelativePositionToFather() const ;
         
          void setRelativePositionToFather(const tarch::la::Vector<Dimensions,int>& relativePositionToFather) ;
         
          int getRelativePositionToFather(int elementIndex) const ;
         
          void setRelativePositionToFather(int elementIndex, const int& relativePositionToFather) ;
         
         /**
          * Generated
          */
         static std::string toString(const DataExchangeType& param);
         
         /**
          * Generated
          */
         static std::string getDataExchangeTypeMapping();
         
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
         GridTraversalEvent convert() const;
         
         
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

