package com.Application.CreditAdministration.repositoriesTest;

import com.Application.CreditAdministration.entities.FileEntity;
import com.Application.CreditAdministration.repositories.FileRepository;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.orm.jpa.DataJpaTest;
import org.springframework.boot.test.autoconfigure.orm.jpa.TestEntityManager;
import org.springframework.test.context.ActiveProfiles;

import java.util.Optional;

import static org.assertj.core.api.Assertions.assertThat;

@DataJpaTest
@ActiveProfiles("test")
public class FileRepositoryTest {

    @Autowired
    private TestEntityManager entityManager;

    @Autowired
    private FileRepository fileRepository;

    @Test
    public void whenFindByCreditIdAndType_thenReturnFile(){
        //given
        FileEntity file = new FileEntity(null,1,"pdf",1,null);
        entityManager.persistAndFlush(file);

        //when
        FileEntity found = fileRepository.findByCreditIdAndType(file.getCreditId(),file.getType());

        //then
        assertThat(found.getCreditId()).isEqualTo(file.getCreditId()).isEqualTo(file.getType());
    }

    @Test
    public void whenFindByCreditId_thenReturnFile(){
        //given
        FileEntity file = new FileEntity(null,1,"pdf",1,null);
        entityManager.persistAndFlush(file);

        //when
        FileEntity found = fileRepository.findByCreditId(file.getCreditId());

        //then
        assertThat(found.getCreditId()).isEqualTo(file.getCreditId());
    }

    @Test
    public void whenDeleteByCreditId_thenReturnVoid(){
        //given
        FileEntity file = new FileEntity(null,1,"pdf",1,null);
        entityManager.persistAndFlush(file);

        //when
        fileRepository.deleteByCreditId(file.getCreditId());
        entityManager.flush();

        //then
        Optional<FileEntity> deletedCredit = Optional.ofNullable(fileRepository.findByCreditId(file.getCreditId()));
        assertThat(deletedCredit).isEmpty();
    }
}
