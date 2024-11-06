package com.Application.CreditAdministration.repositories;

import com.Application.CreditAdministration.entities.CreditEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.ArrayList;

@Repository
public interface CreditRepository extends JpaRepository<CreditEntity,Long> {

    CreditEntity findByCreditId(long creditId);
    ArrayList<CreditEntity> findByCreditUserId(long creditUserId);
    ArrayList<CreditEntity> findByCreditPhase(int creditPhase);
}
