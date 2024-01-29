import matplotlib.pyplot as plt

conf_cube = list(map(float, open('build/model.txt').read().split('\n')))
conf_PGU = list(map(float, open('build/pgu.txt').read().split('\n')))
xarr_cube, yarr_cube, zarr_cube, xarr_PGU, yarr_PGU, zarr_PGU = [], [], [], [], [], []


st = set()
cnt = 0
for i in range(0, len(conf_cube) - 2, 3):
    xarr_cube.append(conf_cube[i])
    yarr_cube.append(conf_cube[i + 1])
    zarr_cube.append(conf_cube[i + 2])
    if (xarr_cube[i//3], yarr_cube[i//3], zarr_cube[i//3]) in st:
        cnt += 1
    st.add((xarr_cube[i//3], yarr_cube[i//3], zarr_cube[i//3]));


for i in range(0, len(conf_PGU) - 2, 3):
    xarr_PGU.append(conf_PGU[i])
    yarr_PGU.append(conf_PGU[i + 1])
    zarr_PGU.append(conf_PGU[i + 2])
    if (xarr_PGU[i//3], yarr_PGU[i//3], zarr_PGU[i//3]) in st:
        cnt += 1
    st.add((xarr_PGU[i//3], yarr_PGU[i//3], zarr_PGU[i//3]));
print(cnt)

fig = plt.figure()
ax = plt.axes(projection='3d')
ax.scatter(xarr_cube, yarr_cube, zarr_cube, color="green")
# ax.scatter(xarr_PGU, yarr_PGU, zarr_PGU, color="red")
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.show()