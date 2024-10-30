package com.example.demo.repositories;

import com.example.demo.entities.fileEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface fileRepository extends JpaRepository<fileEntity,Long> {

    fileEntity getByCreditIdAndType(long creditId,int type);
    fileEntity deleteByCreditId(long creditId);
}
