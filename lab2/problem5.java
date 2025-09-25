public class problem5 {
    public static void main(String[] args) {
        int[] jobIds= {1,2,3,4,5,6,7,8,9,10,11};
        int[] jobSizes ={5760,4190,3290,2030,2550,6990,8940,740,3930,6890,6580};
        int[] blockIds= {1,2,3,4,5,6,7,8,9,10};
        int[] blockSizes ={9500,7000,4500,8500,3000,9000,1000,5500,1500,500};
        logicRun("First-Fit", jobIds, jobSizes, blockIds, blockSizes, true);
        logicRun("Best-Fit",jobIds, jobSizes, blockIds, blockSizes, false);
    }
    public static void logicRun(String title, int[] jobs, int[] jobSizes,int[] blocks, int[] blockSizes, boolean firstFit) {
        int nJobs = jobs.length;
        int nBlocks = blocks.length;
        int[] blockJob = new int[nBlocks];
        for (int i =0; i< nBlocks;i++)blockJob[i] = -1;
        int[] jobToBlock =new int[nJobs];
        int jobsAllocated = 0;
        int internalFrag = 0;
        int externalFrag = 0;
        for (int j = 0; j < nJobs; j++) {
            int jobId = jobs[j];
            int jobSize =jobSizes[j];
            int chosen =-1;
            if (firstFit){
                for (int b = 0; b <nBlocks; b++) {
                    if (blockJob[b] ==-1 && blockSizes[b]>=jobSize) {
                        chosen = b;
                        break;
                    }
                }
            } else {
                int bestSize = Integer.MAX_VALUE;
                for (int b = 0; b < nBlocks; b++) {
                    if (blockJob[b] == -1 && blockSizes[b] >= jobSize) {
                        if (blockSizes[b] < bestSize) {
                            bestSize = blockSizes[b];
                            chosen = b;
                        }
                    }
                }
            }
            if (chosen != -1) {
                blockJob[chosen] = jobId;
                jobToBlock[j] = blocks[chosen];
                jobsAllocated++;
            } else {
                jobToBlock[j] = 0; 
            }
        }
        int totalMem = 0;
        for (int size : blockSizes) totalMem += size;
        for (int b = 0; b < nBlocks; b++) {
            if (blockJob[b] != -1) {
                int jobIndex = -1;
                for (int j = 0; j < nJobs; j++)
                    if (jobs[j] == blockJob[b]) jobIndex = j;
                internalFrag += (blockSizes[b] - jobSizes[jobIndex]);
            } else {
                externalFrag += blockSizes[b];
            }
        }
        double unusedPct = 100.0 * (internalFrag + externalFrag) / totalMem;
        System.out.println("Strategy:" + title);
        System.out.println("Allocations (job--block):");
        for (int j = 0; j < nJobs; j++) {
            if (jobToBlock[j] == 0)
                System.out.println("  Job " + jobs[j] + "--unallocated");
            else
                System.out.println("  Job " + jobs[j] + "--Block" + jobToBlock[j]);
        }
        System.out.println("Total Jobs Allocated: " + jobsAllocated);
        System.out.println("Total Internal Fragmentation: " + internalFrag + " KB");
        System.out.println("Total External Fragmentation: " + externalFrag + " KB");
        System.out.println("Unused Memory Percentage: "  + unusedPct);
    }
}
