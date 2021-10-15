using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using System.Reflection;

namespace ExercisesDAL
{
    public class SomeSchoolRepository<T> : IRepository<T> where T : SchoolEntity
    {
        readonly private SomeSchoolContext _db = null;

        public SomeSchoolRepository(SomeSchoolContext context = null)
        {
            _db = context ?? new SomeSchoolContext();
        }
        
       
        public async Task<List<T>> GetAll()
        {
            return await _db.Set<T>().ToListAsync();
        }

        public async Task<T> GetOne(Expression<Func<T, bool>> match)
        {
            return await _db.Set<T>().FirstOrDefaultAsync(match);
        }

        public async Task<List<T>> GetSome(Expression<Func<T, bool>> match)
        {
            return await _db.Set<T>().Where(match).ToListAsync();
        }

        public async Task<T> Add(T entity)
        {
            _db.Set<T>().Add(entity);
            await _db.SaveChangesAsync();
            return entity;
        }

        public async Task<int> Delete(int id)
        {
            T currentEntity = await GetOne(ent => ent.Id == id);
            _db.Set<T>().Remove(currentEntity);
            return _db.SaveChanges();
        }

        public async Task<UpdateStatus> Update(T entity)
        {
            UpdateStatus operationStatus = UpdateStatus.Failed;
            try
            {
                T currentEntity = await GetOne(ent => ent.Id == entity.Id);
                _db.Entry(currentEntity).OriginalValues["Timer"] = entity.Timer;
                _db.Entry(currentEntity).CurrentValues.SetValues(entity);
                if (await _db.SaveChangesAsync() == 1)
                {
                    operationStatus = UpdateStatus.Ok;
                }
            }
            catch (DbUpdateConcurrencyException dbx)
            {
                operationStatus = UpdateStatus.Stale;
                Console.WriteLine("Problem in " + MethodBase.GetCurrentMethod().Name + dbx.Message);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Problem in " + MethodBase.GetCurrentMethod().Name + ex.Message);
            }
            return operationStatus;
        }
    }
}
