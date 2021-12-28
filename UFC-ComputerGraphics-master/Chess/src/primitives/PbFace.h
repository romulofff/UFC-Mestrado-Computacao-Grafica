// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil

#ifndef PB_FACE_H
#define PB_FACE_H

#include "PbVertex.h"
#include "PbVector.h"
#include <vector>

class PbFace {
	public:
		PbFace();
        PbFace(PbVertex* v1, PbVertex* v2, PbVertex* v3);

		// all bellow automatically update center and normal
        void setVertexV1(PbVertex* v1);
        void setVertexV2(PbVertex* v2);
        void setVertexV3(PbVertex* v3);
        void setVertices(PbVertex* v1, PbVertex* v2, PbVertex* v3);

        PbVertex getCenter() {return center;}
        PbVector getNormal() {return normal;}

        std::vector<PbVertex*>& getVertexVector() {return vertexVector;}

	protected:
        std::vector<PbVertex*> vertexVector;
		PbVertex center;
		PbVector normal;

		PbVector calculateNormal();
		PbVertex calculateCenter();
};

#endif // PB_FACE_H
