package com.Application.CreditAdministration.repositoriesTest;

import com.Application.CreditAdministration.entities.UserEntity;
import com.Application.CreditAdministration.repositories.UserRepository;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.boot.test.autoconfigure.orm.jpa.TestEntityManager;
import org.springframework.test.context.ActiveProfiles;

import static org.assertj.core.api.AssertionsForClassTypes.assertThat;

@DataJpaTest
@ActiveProfiles("test")
public class UserRepositoryTest {

    @Autowired
    private TestEntityManager entityManager;

    @Autowired
    private UserRepository userRepository;

    @Test
    public void whenFindByUserRut_thenReturnUser(){
        //given
        UserEntity user = new UserEntity(null,"John Doe","12345678-9","email","1234",30,10,5,0,20000000,false,false);
        entityManager.persistAndFlush(user);

        //when
        UserEntity found = userRepository.findByUserRut(user.getUserRut());

        //then
        assertThat(found.getUserRut()).isEqualTo(user.getUserRut());
    }

    @Test
    public void whenFindByUserId_thenReturnUser(){
        //given
        UserEntity user = new UserEntity(null,"John Doe","12345678-9","email","1234",30,10,5,0,20000000,false,false);
        entityManager.persistAndFlush(user);

        //when
        UserEntity found = userRepository.findByUserId(user.getUserId());

        //then
        assertThat(found.getUserId()).isEqualTo(user.getUserId());
    }

    @Test
    public void whenFindByUserEmail_thenReturnUser(){
        //given
        UserEntity user = new UserEntity(null,"John Doe","12345678-9","email","1234",30,10,5,0,20000000,false,false);
        entityManager.persistAndFlush(user);

        //when
        UserEntity found = userRepository.findByUserEmail(user.getUserEmail());

        //then
        assertThat(found.getUserEmail()).isEqualTo(user.getUserEmail());
    }
}
