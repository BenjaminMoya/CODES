package com.Application.CreditAdministration.repositoriesTest;

import com.Application.CreditAdministration.entities.CreditEntity;
import com.Application.CreditAdministration.repositories.CreditRepository;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.boot.test.autoconfigure.orm.jpa.TestEntityManager;
import org.springframework.test.context.ActiveProfiles;

import java.util.List;
import static org.assertj.core.api.Assertions.assertThat;

@DataJpaTest
@ActiveProfiles("test")
public class CreditRepositoryTest {

    @Autowired
    private TestEntityManager entityManager;

    @Autowired
    private CreditRepository creditRepository;

    @Test
    public void whenFindByCreditId_thenReturnCredit(){
        //given
        CreditEntity credit = new CreditEntity(null,1,100000000,50000000,120000000,1,20,"27-10-2024",1,"");
        entityManager.persistAndFlush(credit);

        //when
        CreditEntity found = creditRepository.findByCreditId(credit.getCreditId());

        //then
        assertThat(found.getCreditId()).isEqualTo(credit.getCreditId());
    }

    @Test
    public void whenFindByCreditUserId_thenReturnCredits(){
        //given
        CreditEntity lowCredit = new CreditEntity(null,1,100000000,50000000,120000000,1,20,"27-10-2024",1,"");
        CreditEntity highCredit = new CreditEntity(null,1,100000000,100000000,120000000,1,20,"27-10-2024",1,"");
        CreditEntity noRelationCredit = new CreditEntity(null,2,100000000,100000000,120000000,1,20,"27-10-2024",1,"");
        entityManager.persist(lowCredit);
        entityManager.persist(highCredit);
        entityManager.persist(noRelationCredit);
        entityManager.flush();

        //when
        List<CreditEntity> foundCredits = creditRepository.findByCreditUserId(lowCredit.getCreditUserId());

        //then
        assertThat(foundCredits).hasSize(2).extracting(CreditEntity::getCreditUserId).containsOnly(1L);
    }

    @Test
    public void whenFindByCreditPhase_thenReturnCredits(){
        //given
        CreditEntity firstCredit = new CreditEntity(null,1,100000000,50000000,120000000,3,20,"27-10-2024",1,"");
        CreditEntity secondCredit = new CreditEntity(null,10,100000000,100000000,120000000,3,20,"27-10-2024",1,"");
        CreditEntity noRelationCredit = new CreditEntity(null,2,100000000,100000000,120000000,1,20,"27-10-2024",1,"");
        entityManager.persist(firstCredit);
        entityManager.persist(secondCredit);
        entityManager.persist(noRelationCredit);
        entityManager.flush();

        //when
        List<CreditEntity> foundCredits = creditRepository.findByCreditPhase(firstCredit.getCreditPhase());

        //then
        assertThat(foundCredits).hasSize(2).extracting(CreditEntity::getCreditPhase).containsOnly(3);
    }
}
