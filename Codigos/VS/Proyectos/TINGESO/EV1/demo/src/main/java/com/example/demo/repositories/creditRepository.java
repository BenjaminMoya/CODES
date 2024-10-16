package com.example.demo.repositories;

import com.example.demo.entities.creditEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface creditRepository extends JpaRepository<creditEntity,Long> {

    List<creditEntity> findByCreditUserId(long creditUserId);
}
