package com.example.demo.repositories;

import com.example.demo.entities.fileEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.Optional;

@Repository
public interface fileRepository extends JpaRepository<fileEntity, Long> {

    Optional<fileEntity> findByFileCreditIdAndType(long fileUserId,int type);
}
