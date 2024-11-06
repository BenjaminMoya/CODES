package com.Application.CreditAdministration.repositories;

import com.Application.CreditAdministration.entities.FileEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface FileRepository extends JpaRepository<FileEntity,Long> {

    FileEntity findByCreditIdAndType(long creditId, int type);
    FileEntity findByCreditId(long creditId);
    void deleteByCreditId(long creditId);
}
