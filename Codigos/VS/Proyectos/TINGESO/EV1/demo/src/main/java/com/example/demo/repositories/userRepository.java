package com.example.demo.repositories;
import com.example.demo.entities.userEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

@Repository
public interface userRepository extends JpaRepository<userRepository,Long> {

    public userRepository findByRut(long id);

    @Query(value = "SELECT * FROM user WHERE user.rut = :rut",nativeQuery = true)
    userEntity findByRutNativeQuery(@Param("rut") String rut);
}
