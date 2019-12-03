# This file is part of the Peano project. For conditions of distribution and
# use, please see the copyright notice at www.peano-framework.org
from peano4.datamodel.ModelToDataRepository import ModelToDataRepository


class Model(object):
  def __init__(self,namespace):
    self.cell_data   = []
    self.face_data   = []
    self.vertex_data = []
    self.namespace   = namespace
    self.generator   = ModelToDataRepository(self)

  def add_cell(self,submodel):
    submodel.configure(self.namespace + ["celldata"])
    self.cell_data.append(submodel)

  def add_face(self,submodel):
    submodel.configure(self.namespace + ["facedata"])
    self.face_data.append(submodel)

  def add_vertex(self,submodel):
    submodel.configure(self.namespace + ["vertexdata"])
    self.vertex_data.append(submodel)

  def construct_output(self,output):
    for i in self.cell_data:
      i.generator.construct_output(output)
    for i in self.face_data:
      i.generator.construct_output(output)
    for i in self.vertex_data:
      i.generator.construct_output(output)
    self.generator.construct_output(output)





    