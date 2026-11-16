| Command | Mean Wall Time [ms] | Change | Factor |
|:---|---:|---:|:---|
| `./matmul_O0 50 ijk` | 1.3 ± 0.4 |  |  |
| `./matmul_O0 50 ikj` | 1.3 ± 0.3 | -2.9% |  |
| `./matmul_O3 50 ijk` | 1.2 ± 0.2 | -11.0% |  |
| `./matmul_O3 50 ikj` | 1.1 ± 0.2 | -18.0% |  |
| `./matmul_O0 250 ijk` | 21.8 ± 2.6 | +1539.5% | (16.4x slower) |
| `./matmul_O0 250 ikj` | 18.9 ± 0.4 | +1323.1% | (14.2x slower) |
| `./matmul_O3 250 ijk` | 9.4 ± 0.4 | +604.7% | (7.0x slower) |
| `./matmul_O3 250 ikj` | 3.0 ± 0.1 | +125.5% | (2.3x slower) |
| `./matmul_O0 500 ijk` | 139.9 ± 1.2 | +10435.8% | (105.4x slower) |
| `./matmul_O0 500 ikj` | 139.3 ± 0.8 | +10388.2% | (104.9x slower) |
| `./matmul_O3 500 ijk` | 83.1 ± 3.5 | +6156.5% | (62.6x slower) |
| `./matmul_O3 500 ikj` | 16.4 ± 0.9 | +1131.1% | (12.3x slower) |
| `./matmul_O0 750 ijk` | 561.4 ± 25.8 | +42172.5% | (422.7x slower) |
| `./matmul_O0 750 ikj` | 470.9 ± 5.1 | +35352.4% | (354.5x slower) |
| `./matmul_O3 750 ijk` | 293.2 ± 3.8 | +21973.0% | (220.7x slower) |
| `./matmul_O3 750 ikj` | 50.7 ± 0.3 | +3718.6% | (38.2x slower) |
