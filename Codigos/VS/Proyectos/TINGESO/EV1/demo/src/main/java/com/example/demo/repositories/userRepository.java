package com.example.demo.repositories;
import com.example.demo.entities.userEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

@Repository
public interface userRepository extends JpaRepository<userEntity,Long> {

    userEntity findByUserRut(String userRut);
    userEntity findByUserName(String userName);
    userEntity findByUserId(long userId);
    userEntity findByUserEmail(String userEmail);
}
