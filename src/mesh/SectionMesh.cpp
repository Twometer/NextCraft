//
// Created by twome on 26/01/2020.
//

#include "SectionMesh.h"

SectionMesh::SectionMesh(chunk::Section *section) {
    this->section = section;
    this->xo = section->x << 4;
    this->yo = section->y << 4;
    this->zo = section->z << 4;
}

void SectionMesh::Render() {

}

void SectionMesh::Build() {

}

void SectionMesh::Upload() {

}
