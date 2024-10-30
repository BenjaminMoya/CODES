package com.example.demo.entities;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Table(name = "files")
@Data
@NoArgsConstructor
@AllArgsConstructor
public class fileEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(unique = true,nullable = false)
    private long fileId;

    private long creditId;
    private String filename;

    // 1=CI,2=CA,3=HC,4=EPV,5=EFN,6=PDN,7=PR,8=CAA,9=Contrato
    private int type;

    @Lob
    private byte[] fileContent;
}
