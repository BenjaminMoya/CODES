package com.Application.CreditAdministration.repositories;

import com.Application.CreditAdministration.entities.UserEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface UserRepository extends JpaRepository<UserEntity,Long> {

    UserEntity findByUserRut(String userRut);
    UserEntity findByUserId(long userId);
    UserEntity findByUserEmail(String userEmail);
}
